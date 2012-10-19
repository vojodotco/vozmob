Drupal.behaviors.audiorecorderfield = function (context) {
	if (!deployJava.isWebStartInstalled("1.4.2"))
    {
      //Java is not Enabled
      $(".nanogong-fallback").show();
      $(".nanogong-recorder").hide();
      $(".nanogong-upload").hide();
    }
}


/*
function submitVoice(field_name,delta) { 
  if (!deployJava.isWebStartInstalled("1.4.2")) {
    //Java is not Enabled
    submitUpload(field_name,delta)
  }
  else {
    submitRecording(field_name,delta);
  }
}

function submitUpload(field_name,delta) {
  alert("Uploading");
}*/

function submitVoice(field_name,delta) { 
	//Remove any error messages
	$("#edit-field-"+field_name+"-"+delta+"-wrapper .error").remove();
	//Disable the button
	$("#nanogong-button-"+field_name+"-"+delta).attr('disabled', 'disabled');	
	
	if($("#nanogong-button-"+field_name+"-"+delta).val()=='Upload'){
	//Upload button
		
		// Find the applet object 
		//var applet = document.getElementById("nanogong-"+delta); 
		var applet = $("#nanogong-"+field_name+"-"+delta).get(0); 
		// Tell the applet to post the voice recording to the backend PHP code 
		var path=Drupal.settings.basePath +"?q=audiorecorderfield_file_receive";
		
		var fid = applet.sendGongRequest( "PostToForm", path, "voicefile", "", "temp"); 
		if (fid == null || fid == ""){
		$("#nanogong-button-"+field_name+"-"+delta).removeAttr("disabled");
		$("#edit-field-"+field_name+"-"+delta+"-wrapper").append('<div class="messages error file-upload-js-error">Failed to submit the voice recording!</div>');

		} 
		else{
			$.ajax({
					type: "GET",
					url: Drupal.settings.basePath +"?q=audiorecorderfield_file_preview",
					data: "fid=" + fid+"&field_name=" + field_name+"&delta=" +delta,
					dataType: 'json',
					success: NanogongPreview
				});
			$("#edit-field-"+field_name+"-"+delta+"-fid").val(fid);
		} 
	}
	else{
		//Remove button
        $("#edit-field-"+field_name+"-"+delta+"-wrapper .filefield-file-info").remove();
	    $("#edit-field-"+field_name+"-"+delta+"-fid").val("");
	    $("#nanogong-button-"+field_name+"-"+delta).removeAttr("disabled");
	    $("#nanogong-button-"+field_name+"-"+delta).val('Upload');
        $.ajax({
				    type: "GET",
					url: Drupal.settings.basePath +"?q=audiorecorderfield_recorder_reload",
					data: "field_name=" + field_name+"&delta=" +delta,
					dataType: 'json',
					success:  function (data) {
                      //$("#edit-field-"+field_name+"-"+delta+"-wrapper div").remove();
                      //$("#edit-field-"+field_name+"-"+delta+"-wrapper").append(data.recorder);
                      $("#audiorecorderfield-"+field_name+"-"+delta+"-wrapper").html(data.recorder);
                      Drupal.attachBehaviors("#audiorecorderfield-"+field_name+"-"+delta+"-wrapper");
                    }
	    });
	}
} 

function NanogongPreview(data){
	//$("#edit-field-"+data.field_name+"-"+data.delta+"-wrapper").append(data.preview);
	//Remove Upload button and add Remove button
	$("#nanogong-button-"+data.field_name+"-"+data.delta).removeAttr("disabled");
	$("#nanogong-button-"+data.field_name+"-"+data.delta).val('Remove');
	$("#nanogong-"+data.field_name+"-"+data.delta+"-wrapper").remove();
	$("#nanogong-button-"+data.field_name+"-"+data.delta).before(data.player);
}
