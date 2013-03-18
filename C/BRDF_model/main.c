/*
 *  Date:   Jun 19, 2009
 *  Author:	jasonleakey
 *  Change Log:
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 *  main.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include "brdf.h"
#include <math.h>
#include <time.h>
#include <unistd.h>

#define  MAX_KD  1
#define MIN_KD  0.001
#define MAX_KS  100
#define MIN_KS  1
#define MAX_A  5
#define MIN_A  0.01
#define MAX_B  0.1
#define MIN_B  0.01
#define INTERVAL_KD  0.001
#define INTERVAL_KS  2
#define INTERVAL_A  0.01
#define INTERVAL_B  0.01

#define s 0.05760
#define d 4e-4
#define HIGH_PRECISION 1e-4
#define LOW_PRECISION 0.1
#if defined(J_BRDF)
	#define ANGLE_SEL_CNT 369
#elif defined(M_BRDF)
	#define ANGLE_SEL_CNT 203
#endif
#define WAVE_SEL_CNT 697

#define DEG_TO_RAD(A) (A) * pi / 180

#define KD for (Kd = MIN_KD; Kd < MAX_KD + HIGH_PRECISION; Kd += INTERVAL_KD)
#define KS for (Ks = MIN_KS; Ks < MAX_KS + HIGH_PRECISION; Ks += INTERVAL_KS)
#define A for (a = MIN_A; a < MAX_A + HIGH_PRECISION; a += INTERVAL_A)
#define B for (b = MIN_B; b < MAX_B + HIGH_PRECISION; b += INTERVAL_B)
#define RADMON (double)rand() / (RAND_MAX + 1.0)

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	int m = 0;
	int k = 0;

	char lineBuf[MAX_LINE_LEN];
	FILE* brdfStream = NULL;
	FILE* Ei_maxStream = NULL;

	angle_irr_t angleIrr[ANGLE_INFO_CNT];
	wave_irr_t Ei_max[WAVE_INFO_CNT];

	double fr_model = 0.0;
	static double fr_measure[ANGLE_INFO_CNT][WAVE_INFO_CNT] = {{0.0}};
	/* 1 / (pi * cos(Itheta)) */
	static double frmPart_1[ANGLE_INFO_CNT][WAVE_INFO_CNT] = {{0.0}};
	/* -pow(4 * pi * cos(Itheta), 2) */
	static double frmPart_2[ANGLE_INFO_CNT][WAVE_INFO_CNT] = {{0.0}};
	/* pow(pi, 3) / (cos(Itheta) * cos(Rtheta)) * pow(cos(Itheta) + cos(Rtheta), 4) */
#ifdef J_BRDF
	static double frmPart_3[ANGLE_INFO_CNT][WAVE_INFO_CNT] = {{0.0}};
	/* -pow(pi, 2)  * (pow(sin(Itheta), 2) + pow(sin(Rtheta, 2))
	 *       + 2 * sin(Itheta) * sin(Rtheta) * cos(Iphi - Rphi))
	 */
	static double frmPart_4[ANGLE_INFO_CNT][WAVE_INFO_CNT] = {{0.0}};
#endif

	double Ex = 0.0;
	double Ex_new = 0.0;
	double delta = 0.0;
	double T = 4;
	double numerator = 0.0;
	double denominator = 0.0;
	double Ex_min = 0.0;
	double err_30_min = 1.0;
	double err_45_min = 1.0;
	double err_60_min = 1.0;
	double fr_models = 1.0;
	double fr_measures = 0.0;
	/* 径向方向峰值周围10度内的测量角度的序号 */
	/* 这样的角度的个数 */
	short valid_angle_cnt = 0;

	const int intervalAngle = (ANGLE_INFO_CNT - 1) / (ANGLE_SEL_CNT -1);
	const int intervalIrr = (WAVE_INFO_CNT - 1)/ (WAVE_SEL_CNT - 1);

	double Kd = 0.0;
	double Ks = 0.0;
	double a = 0.0;
	double b = 0.0;

	double finalKd = 0.0;
	double finalKs = 0.0;
	double finalA = 0.0;
	double finalB = 0.0;

	srand((unsigned int)time(0));

/****************************************************/

#if defined(J_BRDF)
	if (NULL == (brdfStream = fopen("/home/jasonleakey/090606/J.brdf", "rb")))
#elif defined(M_BRDF)
	if (NULL == (brdfStream = fopen("/home/jasonleakey/090610/M.brdf", "rb")))
#endif
	{
		fprintf(stderr, "fopen():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		return EXIT_FAILURE;
	}

	if (ANGLE_INFO_CNT > fread(angleIrr,\
			sizeof(angle_irr_t), ANGLE_INFO_CNT, brdfStream))
	{
		fclose(brdfStream);
		return EXIT_FAILURE;
	}

#if defined(J_BRDF)
	if (NULL == (Ei_maxStream = fopen("/home/jasonleakey/090610/Ei_max.txt", "r")))
#elif defined(M_BRDF)
	if (NULL == (Ei_maxStream = fopen("/home/jasonleakey/090610/Ei_max.txt", "r")))
#endif
	{
		fclose(brdfStream);
		fprintf(stderr, "fopen():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		return EXIT_FAILURE;
	}

	for (m = 0; m < WAVE_INFO_CNT; m++)
	{
		memset(lineBuf, '\0', sizeof(lineBuf));
		if (NULL == fgets(lineBuf, MAX_LINE_LEN, Ei_maxStream))
		{
			fprintf(stderr, "fgets():%s, Line %d in %s\n", strerror(errno),\
					__LINE__, __FILE__);
			fclose(brdfStream);
			fclose(Ei_maxStream);
			return EXIT_FAILURE;
		}

		char* p = NULL;

		if (0 != strlen(lineBuf))
		{
			if (NULL != (p = strtok(lineBuf, " ")))
			{
				Ei_max[m].lambda = atof(p);
			}

			if (NULL != (p = strtok(NULL, "\r")))
			{
				Ei_max[m].irr = atof(p);
			}
		}
	}
/*****************************************************************/

	for (i = 0; i < ANGLE_INFO_CNT; i += intervalAngle)
	{
#ifdef J_BRDF
		/* 选择峰值附近的数据 */
		/* if (abs(angleIrr[i].Iphi - 270) < LOW_PRECISION\
				&& abs(angleIrr[i].Rtheta - angleIrr[i].Itheta) < 10 + HIGH_PRECISION) */
#endif
		{

#ifdef J_BRDF
			/*if (abs(angleIrr[i].Itheta - 30) < HIGH_PRECISION\
					|| abs(angleIrr[i].Itheta - 45) < HIGH_PRECISION)
			{
				angleIrr[i].Rtheta -= 1.5;
			}
			else
			{
				angleIrr[i].Rtheta -= 1;
			}*/
#endif
			for (j = 0; j < WAVE_INFO_CNT; j += intervalIrr)
			{
				double Itheta = angleIrr[i].Itheta;
				double Iphi = angleIrr[i].Iphi;

				double Rtheta = angleIrr[i].Rtheta;

				double Rphi = angleIrr[i].Rphi;
#ifdef J_BRDF
				/*if (abs(Rphi - 90) < 0.1)
				{
					Rphi = 90;
				}*/
#endif
				double lambda = angleIrr[i].wave_irr[j].lambda * 1e-3; /* unit is nm */
#ifdef J_BRDF
				double cosI_R = cos(DEG_TO_RAD(Iphi - Rphi));
				if (abs(Iphi - 270) < 0.1 && abs(Rphi - 90) < 0.1)
				{
					cosI_R = -1;
				}
#endif

				frmPart_1[i][j] = cos(DEG_TO_RAD((Rtheta - 60))) / pi;
				frmPart_2[i][j] = -pow(4 * pi * cos(DEG_TO_RAD(Itheta)), 2);
#ifndef M_BRDF
				frmPart_3[i][j] = pow(pi, 3) / (cos(DEG_TO_RAD(Itheta))\
					* cos(DEG_TO_RAD(Rtheta)))\
					* pow(sin(DEG_TO_RAD(Itheta)) + sin(DEG_TO_RAD(Rtheta)), 1/8);
				frmPart_4[i][j] = -pow(pi, 2)  * (pow(sin(DEG_TO_RAD(Itheta)), 2)\
					+ pow(sin(DEG_TO_RAD(Rtheta)), 2)\
					+ 2 * sin(DEG_TO_RAD(Itheta)) * sin(DEG_TO_RAD(Rtheta))\
					* cosI_R);

#endif

#if defined(J_BRDF)
				fr_model = Kd * frmPart_1[i][j] * exp(frmPart_2[i][j] * pow(b / lambda, 2))\
					+ Ks * pow(a * b , 2) / pow(lambda, 4) * frmPart_3[i][j]\
					* exp(frmPart_4[i][j] * pow(a / lambda, 2));
#elif defined(M_BRDF)
			fr_model = Kd * frmPart_1[i][j] * exp(frmPart_2[i][j] * pow(b / lambda, 2));
#endif

				fr_measure[i][j] = 4 * pow(s, 2) * angleIrr[i].wave_irr[j].irr\
					/ (Ei_max[j].irr * cos(DEG_TO_RAD(Itheta)) * pi * pow(d, 2));

				if (fr_measure[i][j] > 30)
				{
					fr_measure[i][j] = 5;
				}

				numerator += pow(fr_model - fr_measure[i][j], 2);
				denominator += pow(fr_measure[i][j], 2);
			}
		}
	}

	Ex = numerator / denominator; /* denominator is immutable from now on */
	Ex_min = Ex;

/*****************************************************************/
	for(;;)
	{
		//for (b = MIN_B; b < MAX_B - HIGH_PRECISION; b += INTERVAL_B)
		//B
		{
			//for (a = MIN_A; a < MAX_A - HIGH_PRECISION; a += INTERVAL_A)
			//KD
			{
				//for (Ks = MIN_KS; Ks < MAX_KS - HIGH_PRECISION; Ks += INTERVAL_KS)
				//A
				{
					//for (Kd = MIN_KD; Kd < MAX_KD - HIGH_PRECISION; Kd += INTERVAL_KD)
					//KS
					//srand(time(NULL));
					//for(m = 0; m < 1e3; m++)

					for (;;)
					{
						Kd = 100 * RADMON;
#ifndef M_BRDF
						Ks = 300 * RADMON;
						a = 10 * RADMON;
#endif
						b = 0.1 * RADMON;
						numerator = 0.0;
						double errer_30 = 0.0;
						double errer_45 = 0.0;
						double errer_60 = 0.0;
						int N_30 = 0;
						int N_45 = 0;
						int N_60 = 0;
						fr_models = 0.0;

						for (m = 0; m < ANGLE_INFO_CNT; m++)
						{
							for (j = 0; j < WAVE_INFO_CNT; j += intervalIrr)
							{
								/*if (abs(angleIrr[i].Iphi - 270) < HIGH_PRECISION\
										&& abs(angleIrr[i].Rtheta - angleIrr[i].Itheta) < 5)
								{*/
								/* fr_model = Kd / (pi * cos(Itheta)) * exp(-pow(4 * pi * b \
										/ lambda * cos(Itheta), 2)) + Ks / (cos(Itheta) * cos(Rtheta))\
										* pow(pi, 3) * pow(cos(Itheta) + cos(Rtheta), 4) * pow(a / lambda, 2)\
										* pow(b / lambda, 2) * exp(-pow(pi * a / lambda, 2)\
										* (pow(sin(Itheta), 2) + pow(sin(Rtheta), 2)\
										+ 2 * sin(Itheta) * sin(Rtheta) * cos(Iphi - Rphi)));
								*/

									double lambda = angleIrr[m].wave_irr[j].lambda * 1e-3;

#if defined(J_BRDF)
									fr_model = Kd * frmPart_1[m][j]\
										* exp(frmPart_2[m][j] * pow(b / lambda, 2))\
										+ Ks * pow(a * b , 2) * lambda/* / pow(lambda, 4) */ * frmPart_3[m][j]\
										* exp(frmPart_4[m][j] * pow(a / lambda, 2));
#elif defined(M_BRDF)
									fr_model = Kd * frmPart_1[m][j] * exp(frmPart_2[m][j] * pow(b / lambda, 2));
#endif

								/*fr_measure = 4 * pow(s, 2) * angleIrr[i].wave_irr[j].irr\
									/ (Ei_max[j].irr * cos(Itheta) * pi * pow(d, 2));*/

									double _fr_measure = fr_measure[m][j];
									fr_models += pow(fr_model, 2);
									numerator += pow(fr_model - fr_measure[m][j], 2);
									if (fr_measure[m][j] > 0)
									{
										if (abs(angleIrr[m].Itheta - 30) < HIGH_PRECISION)
										{
											errer_30 += fabs((fr_model - fr_measure[m][j])\
												/ fr_measure[m][j]);
											N_30++;
										}
										else if (abs(angleIrr[m].Itheta - 45) < HIGH_PRECISION)
										{
											errer_45 += fabs((fr_model - fr_measure[m][j])\
												/ fr_measure[m][j]);
											N_45++;
										}
										else if (abs(angleIrr[m].Itheta - 60) < HIGH_PRECISION)
										{
											errer_60 += fabs((fr_model - fr_measure[m][j])\
												/ fr_measure[m][j]);
											N_60++;
										}
									}
								}
						}

						Ex_new = numerator / denominator;
						errer_30 = errer_30 / N_30;
						errer_45 = errer_45 / N_45;
						errer_60 = errer_60 / N_60;

						if (1)//(Ex_new < Ex_min\
								|| (errer_30 < 0.9 && errer_45 < 0.9 && errer_60 < 0.9))
						{

							if (Ex_new < Ex_min
								/*&& errer_30 < err_30_min
								&& errer_45 < err_45_min
								&& errer_60 < err_60_min*/)
							{
								srand(time(0));
								Ex_min = Ex_new;
								err_30_min = errer_30;
								err_45_min = errer_45;
								err_60_min = errer_60;
								finalKd = Kd;
								finalKs = Ks;
								finalA = a;
								finalB = b;
							}


							printf("Ex_min=%-12fKd=%-12fKs=%-12fa=%-12fb=%-12f"
									"err_30:%-.2f%%\terr_45:%-.2f%%\terr_60:%-.2f%%\t"
									"err_30_min:%-.2f%%\terr_45_min:%-.2f%%\terr_60_min"
									":%-.2f%%\tfinalKd=%f\tfinalKs=%f\tfinalA=%f\tfinalB=%f\n",\
									Ex_min, Kd, Ks, a, b,\
									100 * errer_30, 100 * errer_45, 100 * errer_60,
									100 * err_30_min, 100 * err_45_min, 100 * err_60_min,
									finalKd, finalKs, finalA, finalB);
							/*if (errer_30 < 0.1 && errer_45 < 0.1 && errer_60 < 0.1)
							{
								srand(time(0));
								printf("err_30:%-.2f%%\terr_45:%-.2f%%\terr_60:%-.2f%%\n",\
									100 * errer_30, 100 * errer_45, 100 * errer_60);
								printf("----->Ex_new=%-12fKd=%-12fKs=%-12fa=%-12fb=%-12f\n",\
									Ex_new, Kd, Ks, a, b);
								return EXIT_SUCCESS;
							}*/
						}

						/*
						delta = Ex_new - Ex;
						 printf("Ex_new = %f\n", Ex_new);
						double randValue = (double)rand() / (RAND_MAX + 1.0);
						if (delta < 0 || exp(-delta / T) > randValue)
						{
							Ex = Ex_new;
							printf("Kd = %f, Ks = %f, a = %f, b = %f, Ex = %.8f || "
									"fr_models = %.8f || "
									"Ex_min = %.8f(Kd=%f, Ks=%f, a=%f, b=%f)\n",\
									Kd, Ks, a, b, Ex, fr_models, Ex_min,\
									finalKd, finalKs, finalA, finalB);
							if (Ex_new < Ex_min)
							{
								srand(time(0));
								Ex_min = Ex_new;
								finalKd = Kd;
								finalKs = Ks;
								finalA = a;
								finalB = b;
							}
						}*/

						/*if (Ex < 0.1)
						{
							printf("Final:Kd = %f, Ks = %f, a = %f, b = %f\n", Kd, Ks, a, b);
							fclose(brdfStream);
							fclose(Ei_maxStream);
							return EXIT_SUCCESS;
						}*/
					}
				}
			}
		}
		/* T *= 0.9; */
	}


	return EXIT_SUCCESS;
}

