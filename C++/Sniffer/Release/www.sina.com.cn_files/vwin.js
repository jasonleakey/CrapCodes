//2009-01-15
var _IE = document.all;
var oswf;
var itv;
try{
	if(v_agent && v_agent!=''){
		//document.write('<div id="v_trace_div" style="position:absolute;top:0;left:0;">&nbsp;</div>');
		document.write('<div id="v_count_div" style="position:absolute;">&nbsp;</div>');
		document.write('<script language="javascript" type="text/javascript" src="'+v_script_url+'"></scr'+'ipt>');
		itv = setInterval(init,100);
	}
}catch(e){}
function init(){
	try{

		//浮层形式
		try{
			oswf = getSwf("videoPlayer");
			if(oswf){
				clearInterval(itv);
				itv = setInterval(detect,100);
				return;
			}
		}catch(e){}

		//兼容旧代码
		if(videoWin){
			try{
				if(v_agent=='iCast'){
					oswf = getWinSwf("iCastPlayer") || getWinSwf("flash");
				}else if(v_agent=='SmartCreative'){
					oswf = getWinSwf("button690") || getWinSwf("hotson");
				}else if(v_agent=='yeazone'){
					oswf = videoWin.document.getElementById("YZAD");
				}
				if(oswf){
					clearInterval(itv);
					itv = setInterval(detect,100);
				}
			}catch(e){}
		}

	}catch(e){}
}
function detect(){
	try{
		var cf = oswf.CurrentFrame()+1;
		var tf = _IE?oswf.TotalFrames:oswf.TotalFrames();
		var per = Math.round(cf/tf*100);
	}catch(e){
		var cf = 1;
		var per=0;
	}
	//document.getElementById('v_trace_div').innerHTML = per+'%';
	for(var i=0; i<v_counter_url.length; i++){
		if(cf>1 && per>=v_counter_url[i].per && !v_counter_url[i].counted){ //播放到x% //访问计数服务器
			v_counter_url[i].counted = true;
			document.getElementById('v_count_div').innerHTML = v_counter_url[i].url;
		}
	}
	if(per>=100) clearInterval(itv);
}
function getWinSwf(id){
	if(_IE){
		return(videoWin.document.getElementById(id));
	}else{
		return(videoWin.document.embeds[id]);
	}
}
function getSwf(id){
	if(_IE){
		return(document.getElementById(id));
	}else{
		return(document.embeds[id]);
	}
}