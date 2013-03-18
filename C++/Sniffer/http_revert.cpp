/*
 *  Sniffer - reconstruct packets containing HTTP message, and revert web page
 *  
 *  Copyright(R) by HuangYetian <jasonleakey@gmail.com>
 *  				HouRuijie	<hourjworld@yahoo.com.cn>
 *  --------------------------------------------------------------------
 *  Sniffer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Sniffer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Sniffer; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "sniffer.h"
#include "http_revert.h"

/*
 * input:
 * 		HttpLNode* list: http packet list
 * 		int start: the beginning index of sublist in the entire list
 * 		int end: the end index of sublist in the entire list
 * 		CMP_KEY key: the key to compare in sort algorithm
 * output:
 * 		void
 * effect:
 * 		provided the HTTP packet list, response or request, using binary
 * 		insertion sorting algorithm to sort the list from index 'start' to
 * 		index 'end'. key is used to compare, and the result is ascending.
 */

void bin_ins_sort(HttpLNode *list, int start, int end, CMP_KEY key)
{
	int i = 0;
	int j = 0;
	int high = 0;
	int low = 0;
	int mid = 0;
	HttpLNode temp;


	// key is Acknowledge
	if (key == CMP_ACK)
	{
		for (i = start + 1; i < end; i++)
		{
			if (list[i].ack < list[i - 1].ack)
			{
				memcpy(&temp, &list[i], sizeof(HttpLNode));
				low = start;
				high = i - 1;
				while (low <= high)
				{
					mid = (low + high) / 2;
					if (temp.ack <= list[mid].ack)
					{
						high = mid - 1;
					}
					else
					{
						low = mid + 1;
					}
				}
				for (j = i - 1; j > high; j--)
				{
					memcpy(&list[j + 1], &list[j], sizeof(HttpLNode));
				}
				memcpy(&list[j + 1], &temp, sizeof(HttpLNode));
			}
		}
	}
	// key is Sequence number
	else
	{
		for (i = start + 1; i < end; i++)
		{
			if (list[i].seq < list[i - 1].seq)
			{
				memcpy(&temp, &list[i], sizeof(HttpLNode));
				low = start;
				high = i - 1;
				while (low <= high)
				{
					mid = (low + high) / 2;
					if (temp.seq <= list[mid].seq)
					{
						high = mid - 1;
					}
					else
					{
						low = mid + 1;
					}
				}
				for (j = i - 1; j > high; j--)
				{
					memcpy(&list[j + 1], &list[j], sizeof(HttpLNode));
				}
				memcpy(&list[j + 1], &temp, sizeof(HttpLNode));
			}
		}
	}
}

/*
 * input:
 * 		HttpLNode* httpRespondPktList: http response packet list
 * 		int start_idx: the beginning index of sublist in the whole list
 * 		int end_idx: the end index of sublist in the whole list
 * 		char* reassemble_data: all http data of a message without http header
 * 		bool* isCompressed: if the http data is compressed,
 * 							isCompressed will be true,otherwise false
 * output:
 * 		int: if all data is correct and no segment in a message lost,
 * 			return the length of reassembled data
 * effect:
 * 		reassemble http message data from the sublist with the same Ack.
 */

static int reassemble_data(HttpLNode *httpRespondPktList,
                           int start_idx,
                           int end_idx,
                           char* reassembled_data,
                           bool* isCompressed)
{
	int reIdx = 0; // the length of reassembled data
	char* pDataStart = NULL;


	// if response message is not version 1.1 or returning a status except 200
	// 	then return fail
	char* pStatus = NULL;
	if (NULL == (pStatus = strstr(httpRespondPktList[start_idx].data,
	                              "200 OK")))
	{
		return -1;
	}

	// get content length of message if Content-Length field is presented.
	int ContentLength = 0;
	char* pContentLength = NULL;
	if (NULL != (pContentLength = strstr(httpRespondPktList[start_idx].data,
	                                     "Content-Length: ")))
	{
		pContentLength += 16;
		char* end = NULL;
		char strContentLen[10];
		memset(strContentLen, '\0', 10);
		end = strchr(pContentLength, '\r');
		strncpy(strContentLen, pContentLength, end - pContentLength);
		ContentLength = atoi(strContentLen);
	}

	// check if 'Content-Encoding' field in present in response message
	// if yes, the message is compressed in gzip format, otherwise not compressed
	char* pContentEncoding = NULL;
	if (NULL != (pContentEncoding = strstr(httpRespondPktList[start_idx].data,
	                                       "Content-Encoding: gzip")))
	{
		*isCompressed = true;
	}

	if (NULL != (pDataStart = strstr(httpRespondPktList[start_idx].data,
	                                 "\r\n\r\n")))
	{
		pDataStart += 4; // jump over "\r\n\r\n"
		// copy data except the http header
		int slen = httpRespondPktList[start_idx].len - short(pDataStart
		        - httpRespondPktList[start_idx].data);
		memcpy(&reassembled_data[reIdx], pDataStart, slen);
		reIdx += slen;
	}

	// copy data from the second segment in sublist
	for (int i = start_idx + 1; i < end_idx; i++)
	{
		if (httpRespondPktList[i].seq == httpRespondPktList[i - 1].seq
		        + httpRespondPktList[i - 1].len)
		{
			// correct message
			memcpy(&reassembled_data[reIdx],
			       httpRespondPktList[i].data,
			       httpRespondPktList[i].len);
			reIdx += httpRespondPktList[i].len;
		}
		else if (httpRespondPktList[i].seq == httpRespondPktList[i - 1].seq
		        && httpRespondPktList[i].len <= httpRespondPktList[i - 1].len)
		{
			continue; // repeated message or sub message - drop
		}
		else if (httpRespondPktList[i].seq > httpRespondPktList[i - 1].seq
		        && httpRespondPktList[i].seq < httpRespondPktList[i - 1].seq
		                + httpRespondPktList[i - 1].len
		        && httpRespondPktList[i].seq + httpRespondPktList[i].len
		                < httpRespondPktList[i - 1].seq + httpRespondPktList[i
		                        - 1].len)
		{
			continue; // partial repeated message with no new data - drop
		}
		else if (httpRespondPktList[i].seq > httpRespondPktList[i - 1].seq
		        && httpRespondPktList[i].seq < httpRespondPktList[i - 1].seq
		                + httpRespondPktList[i - 1].len
		        && httpRespondPktList[i].seq + httpRespondPktList[i].len
		                > httpRespondPktList[i - 1].seq + httpRespondPktList[i
		                        - 1].len)
		{
			int newDataOffset = 0;
			newDataOffset = httpRespondPktList[i - 1].seq
			        + httpRespondPktList[i - 1].len - httpRespondPktList[i].seq;
			memcpy(&reassembled_data[reIdx], httpRespondPktList[i].data
			        + newDataOffset, httpRespondPktList[i].len - newDataOffset);
			reIdx += httpRespondPktList[i].len - newDataOffset;
		}
		else
		{
			cout << "(i-1)SEQ:" << httpRespondPktList[i - 1].seq << endl;
			cout << "(i-1)LEN:" << httpRespondPktList[i - 1].seq << endl;
			cout << "(i)SEQ:" << httpRespondPktList[i - 1].seq << endl;
			cout << "(i)LEN:" << httpRespondPktList[i - 1].seq << endl;
		}
	}
	return ContentLength == 0 || ContentLength == reIdx ? reIdx : -1;
}

/*
 * input:
 * 		char* Path: path of the compressed .gz file
 * 		int file_len: the file size of compressed file
 * output:
 *		int: return 0 if successfully decompressed, otherwise -1
 * effect:
 *		utilize zlib to decompress the gzip-format .gz file,
 *		and save the uncompressed data as another file
 */

static int decompress_data(char* Path, int file_len)
{
	gzFile fp = NULL;
	if (NULL == (fp = gzopen(Path, "rb")))
	{
		fprintf(stderr,
		        "gzopen:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		return -1;
	}

	/*
	 * get all data
	 */
	char buf[MAX_UNCOMPRESSED_DATA_LEN];
	int unlen = 0;
	while (!gzeof(fp))
	{
		buf[unlen++] = gzgetc(fp);
	}
	gzclose(fp);

	if (0 != unlen)
	{
		FILE* hp = NULL;
		char newFileName[MAX_RELATIVE_URL_LEN];
		memset(newFileName, '\0', MAX_RELATIVE_URL_LEN);
		strncpy(newFileName, Path, strlen(Path) - 3); // get rid of ".gz" suffix
		if (NULL == (hp = fopen(newFileName, "w")))
		{
			fprintf(stderr,
			        "fopen:%s, Line %d in %s\n",
			        strerror(errno),
			        __LINE__,
			        __FILE__);
			return -1;
		}

		for (int i = 0; i < unlen; i++)
		{
			fputc(buf[i], hp);
		}
		fclose(hp);
	}

	return 0;
}

//int decompress_data(
//		Bytef* dst,
//		uLongf* dst_len,
//		Bytef* src,
//		uLongf src_len)
//{
//	int ret;
//	z_stream strm;
//
//	*dst_len = compressBound(src_len);
//
//	/* allocate inflate state */
//	strm.zalloc = Z_NULL;
//	strm.zfree = Z_NULL;
//	strm.opaque = Z_NULL;
//	strm.avail_in = src_len;
//	strm.next_in = src;
//	strm.avail_out = *dst_len;
//	strm.next_out = dst;
//
//	ret = inflateInit2(&strm, 47);
//	if (ret != Z_OK)
//		return ret;
//
//	/* run inflate() on input until output buffer not full */
//	while (strm.total_out < *dst_len && strm.total_in < src_len)
//	{
//		strm.avail_in = 1;
//		strm.avail_out = 1;
//		ret = inflate(&strm, Z_NO_FLUSH);
//		assert(ret != Z_STREAM_ERROR); /* state not clobbered */
//		switch (ret)
//		{
//			case Z_NEED_DICT:
//				ret = Z_DATA_ERROR; /* and fall through */
//			case Z_DATA_ERROR:
//			case Z_MEM_ERROR:
//				inflateEnd(&strm);
//				return ret;
//		}
//	}
//	*dst_len = strm.total_out;
//
//	/* clean up and return */
//	(void)inflateEnd(&strm);
//	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
//}

/*
 * input:
 * 		char* filepath: file path
 * 		char* data: data of uncompressed or compressed form
 * 		int data_len: the length of data
 * output:
 * 		bool: if saved successfully, return true, otherwise false
 * effect:
 * 		store data to file with filepath provided
 */

static bool save_file(char* filepath, char* data, int data_len)
{
	FILE* fp = NULL;
	if (NULL == (fp = fopen(filepath, "wb")))
	{
		fprintf(stderr,
		        "fopen:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		return false;
	}
	if (0 == fwrite(data, 1, data_len, fp))
	{
		fprintf(stderr,
		        "fwrite:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		fclose(fp);
		return false;
	}
	fclose(fp);
	return true;
}

/*
 * input:
 * 		char* html_file: the main html file path
 * 		char* website: website filter
 * output:
 * 		int: return 0 if modified successfully, -1 otherwise
 * effect:
 * 		modify hyperlink in 'html' file
 *		i.g before modification: 'src=http://www.baidu.com/image/logo.gif'
 *		after modification: 'src=www.baidu.com_files/logo.gif'
 */
static int modify_html_src_path(char* html_file, char* website)
{
	FILE* fp = NULL;
	if (NULL == (fp = fopen(html_file, "r")))
	{
		fprintf(stderr,
		        "fopen:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		return -1;
	}

	// get all data and store in the buffer
	fseek(fp, 0, SEEK_END);
	long file_len = ftell(fp);
	rewind(fp);
	char* buffer = new char[file_len + 1];
	if (fread(buffer, 1, file_len, fp) < file_len)
	{
		fprintf(stderr,
		        "fread:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		fclose(fp);
		return -1;
	}
	fclose(fp);

	// modify path
	char* pSrc = buffer;
	for (;;)
	{
		// search 'src='
		if (NULL == (pSrc = strstr(pSrc, "src=")))
		{
			break; // no 'src=' found
		}
		else
		{
			// jump over "src="
			pSrc += 4;
			char* pSrcEnd1 = NULL;
			char* pSrcEnd2 = NULL;
			char* pSrcEnd = NULL;
			// if the hyperlink end with space ' ' or '>'
			// return the pointer to the first one to appear
			if (NULL == (pSrcEnd1 = strstr(pSrc, ">")) || NULL == (pSrcEnd2
			        = strstr(pSrc, " ")))
			{
				break; // not found, broken html
			}
			else
			{
				pSrcEnd = (pSrcEnd1 < pSrcEnd2) ? pSrcEnd1 : pSrcEnd2;
				for (; pSrcEnd > pSrc && '/' != *pSrcEnd; pSrcEnd--)
				{
					;
				}
				// cut the hyperlink except filename, and set it '\0'
				if (pSrcEnd > pSrc)
				{
					memset(pSrc, '\0', pSrcEnd - pSrc + 1);
				}
			}
		}
	}

	if (NULL == (fp = fopen(html_file, "w")))
	{
		fprintf(stderr,
		        "fopen:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		return -1;
	}
	for (int i = 0; i < file_len; i++)
	{
		if ('\0' != buffer[i])
		{
			fputc(buffer[i], fp);
		}
		else if ('\0' != buffer[i - 1])
		{
			fputs(website, fp);
		}
	}
	fclose(fp);
	return 0;
}

bool revert_http(HttpLNode *httpRespondPktList,
                 HttpLNode *httpRequestPktList,
                 char* website)
{
	int respondListLen = 0; // length of response message packets list
	int requestListLen = 0; // length of request message packets list
	// get the length of two list
	for (int i = 0; 0 != httpRespondPktList[i].len; i++)
	{
		respondListLen++;
	}
	for (int i = 0; 0 != httpRequestPktList[i].len; i++)
	{
		requestListLen++;
	}

	if (0 == respondListLen || 0 == requestListLen)
	{
		return false;
	}

	// sort the whole response packet list with key Ack
	bin_ins_sort(httpRespondPktList, 0, respondListLen, CMP_ACK);
	// sort the whole request packet list with key Seq
	bin_ins_sort(httpRequestPktList, 0, requestListLen, CMP_SEQ);


	// create directory for storing all configuration and media files of website
	char* elemDirName = new char[MAX_WEBSITE_LEN + 10];
	memset(elemDirName, '\0', MAX_WEBSITE_LEN + 10);
	strcat(strcpy(elemDirName, website), "_files/");
	mkdir(elemDirName, 0777);

	for (int i = 0; i < respondListLen;)
	{
		int startIdx = i; // the begnning index of sublist with the same Ack
		int endIdx = i; // the end index of sublist with the same Ack
		unsigned int curAck = httpRespondPktList[i].ack; // current Ack
		int nTotalLen = 0; // the length of an http message with the http header
		bool bIsCompressed = false; // if the http content is compressed

		// compute the total length
		for (; endIdx < respondListLen && curAck
		        == httpRespondPktList[endIdx].ack; endIdx++)
		{
			nTotalLen += httpRespondPktList[endIdx].len;
		}
		// sort the sublist with same Ack by key Seq
		bin_ins_sort(httpRespondPktList, startIdx, endIdx, CMP_SEQ);

		char* reasmdData = new char[nTotalLen]; // reassembled data
		int effectiveLen = 0; // the length of reassembled data without http header
		memset(reasmdData, '\0', nTotalLen);
		if (!reasmdData)
		{
			return false;
		}
		// reassemble data and compute length, if failed, drop this file, and continue
		if (-1 == (effectiveLen = reassemble_data(httpRespondPktList,
		                                          startIdx,
		                                          endIdx,
		                                          reasmdData,
		                                          &bIsCompressed)))
		{
			fprintf(stderr,
			        "reassemble_data:%s, Line %d in %s\n",
			        strerror(errno),
			        __LINE__,
			        __FILE__);
			cout << "broken package!" << endl;
			i = endIdx;
			continue;
		}

		// search corresponding request message index in request_list
		int reqIdx = 0;
		for (; reqIdx < requestListLen && curAck
		        != httpRequestPktList[reqIdx].seq
		                + httpRequestPktList[reqIdx].len; reqIdx++)
		{
			;
		}
		// not found, fail
		if (reqIdx >= requestListLen)
		{
			i = endIdx;
			continue;
		}

		// store relative URL to array
		char relativeURL[MAX_RELATIVE_URL_LEN];
		char* rp = relativeURL;
		char* pHttp = httpRequestPktList[reqIdx].data;
		pHttp += 4; // jump over 'GET' and ' ' space
		for (; ' ' != *pHttp;)
		{
			*rp++ = *pHttp++;
		}
		*rp = '\0';

		// generate the filename from the header in request message
		char filename[MAX_RELATIVE_URL_LEN];
		memset(filename, '\0', MAX_RELATIVE_URL_LEN);
		char Path[MAX_RELATIVE_URL_LEN]; // the relative path of file
		memset(Path, '\0', MAX_RELATIVE_URL_LEN);
		// the case 'GET / HTTP/1.1' in the first line in request message
		if (strlen(relativeURL) <= 1)
		{
			strcat(strcat(filename, website), ".html");
			// if data is compressed, append .gz suffix in the filename
			bIsCompressed ? strcat(filename, ".gz") : NULL;
			strcat(Path, filename);
		}
		// the case like 'GET /image/xxx.gif HTTP/1.1' in first line in request message
		else
		{
			int k = 0;
			for (k = strlen(relativeURL) - 1; k >= 0 && '/' != relativeURL[k]; k--)
			{
				;
			}
			strcat(filename, &relativeURL[k + 1]);
			// if data is compressed, append .gz suffix in the filename
			bIsCompressed ? strcat(filename, ".gz") : NULL;
			strcat(strcat(Path, elemDirName), filename);
		}
		// save file no matter whether the data is compressed
		if (!save_file(Path, reasmdData, effectiveLen))
		{
			fprintf(stderr,
			        "save_file:%s, Line %d in %s\n",
			        strerror(errno),
			        __LINE__,
			        __FILE__);
			cout << "can't save file!" << endl;
		}

		// if the response message is compressed with gzip format
		// read the file stored above, uncompress and save again
		if (bIsCompressed)
		{
			if (-1 == decompress_data(Path, effectiveLen))
			{
				fprintf(stderr,
				        "decompress:%s, Line %d in %s\n",
				        strerror(errno),
				        __LINE__,
				        __FILE__);
				cout << "could not decompress data!" << endl;
			}
		}
		cout << "Saved File: " << Path << endl;

		// jump to next message with another Ack
		i = endIdx;
		delete[] reasmdData;
	}

	// modify hyperlink in 'html' file
	// i.g before modification: 'src=http://www.baidu.com/image/logo.gif'
	// after modification: 'src=www.baidu.com_files/logo.gif' in local path
	char mainHtmlName[MAX_WEBSITE_LEN];
	memset(mainHtmlName, '\0', MAX_WEBSITE_LEN);
	strcat(strcat(mainHtmlName, website), ".html");
	if (0 == access(mainHtmlName, F_OK))
	{
		modify_html_src_path(mainHtmlName, elemDirName);
	}

	return 0;
}
