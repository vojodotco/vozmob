$(document).ready(function () {
  //var player = getPlayer('haxe');
	/*if (!player || !player.attachHandler) setTimeout(init, 100); // Wait for load
	else {
		player.attachHandler("progress", "FileLoad");
		player.attachHandler("PLAYER_LOAD", "SoundLoad");
		player.attachHandler("PLAYER_BUFFERING", "SoundState", "BUFFERING");
		player.attachHandler("PLAYER_PLAYING", "SoundState", "PLAYING");
		player.attachHandler("PLAYER_STOPPED", "SoundState", "STOPPED");
		player.attachHandler("PLAYER_PAUSED", "SoundState", "PAUSED");
		InfoState = document.getElementById('InfoState')
		Inform();
	}*/
    
    setTimeout(function() {
		var player = getPlayer('haxe');
		//alert("Init events (ver="+player.getVersion()+")");
		player.attachHandler('PLAYER_BUFFERING', "Handler")
	}, 1000);
});

function Handler(event, arg1, arg2) {
	setTimeout("doPlay()", 1000);
}
function getPlayer(pid) {
	var obj = document.getElementById(pid);
	if (obj.doPlay) return obj;
	for(i=0; i<obj.childNodes.length; i++) {
		var child = obj.childNodes[i];
		if (child.tagName == "EMBED") return child;
	}
}
function doPlay(fname) {
	var player = getPlayer('haxe');
	//player.doPlay(fname);
    player.doSeek(0.0);
}
function doStop() {
	var player = getPlayer('haxe');
	player.doStop();
}
var SoundLen = 0;
var SoundPos = 0;
var Last = undefined;
var State = "STOPPED";
var Timer = undefined;
function getPerc(a, b) {
	return ((b==0?0.0:a/b)*100).toFixed(2);
}
function FileLoad(bytesLoad, bytesTotal) {
	document.getElementById('InfoFile').innerHTML = "Loaded "+bytesLoad+"/"+bytesTotal+" bytes ("+getPerc(BytesLoad,BytesTotal)+"%)";
}
function SoundLoad(secLoad, secTotal) {
	document.getElementById('InfoSound').innerHTML = "Available "+secLoad.toFixed(2)+"/"+secTotal.toFixed(2)+" seconds ("+getPerc(secLoad,secTotal)+"%)";
	SoundLen = secTotal;
}
var InfoState = undefined;
function Inform() {
	if (Last != undefined) {
		var now = new Date();
		var interval = (now.getTime()-Last.getTime())/1000;
		SoundPos += interval;
		Last = now;
	}
	InfoState.innerHTML = State + "("+SoundPos.toFixed(2)+"/"+SoundLen.toFixed(2)+" sec ("+getPerc(SoundPos,SoundLen)+"%)";
}
function SoundState(state, position) {
	if (position != undefined) SoundPos = position;
	if (State != "PLAYING" && state=="PLAYING") {
		Last = new Date();
		Timer = setInterval(Inform, 100);
		Inform();
	} else
	if (State == "PLAYING" && state!="PLAYING") {
		clearInterval(Timer);
		Timer = undefined;
		Inform();
	}
	State = state;
	Inform();
}