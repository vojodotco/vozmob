//Drupal.behaviors.audiorecorderfield = function (context) {
$(document).ready(function () {
	Recorder.initialize({
        swfSrc: Drupal.settings.soundcloud_recorder[0]
      });
});

function timecode(ms) {
        var hms = {
          h: Math.floor(ms/(60*60*1000)),
          m: Math.floor((ms/60000) % 60),
          s: Math.floor((ms/1000) % 60)
        };
        var tc = []; // Timecode array to be joined with '.'
        if (hms.h > 0) {
          tc.push(hms.h);
        }
        tc.push((hms.m < 10 && hms.h > 0 ? "0" + hms.m : hms.m));
        tc.push((hms.s < 10  ? "0" + hms.s : hms.s));
        return tc.join(':');
      }
    

      

      function record(field_name, delta){
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-record").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-stop").show();
        Recorder.record({
          start: function(){
            //alert("recording starts now. press stop when youre done. and then play or upload if you want.");
          },
          progress: function(milliseconds){
            //document.getElementById("time-"+field_name+"-"+delta).innerHTML = timecode(milliseconds);
            $("#time-"+field_name+"-"+delta).html(timecode(milliseconds));
          }
        });
      }
      
      function play(field_name, delta){
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-play").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-pause").show();
        //Recorder.stop();
        Recorder.play({
          finished: function(){               
            // will be called when playback is finished
           $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-pause").hide();
           $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-play").show();
          },
          progress: function(milliseconds){
            //document.getElementById("time-"+field_name+"-"+delta).innerHTML = timecode(milliseconds);
            if ($("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-pause").is(":visible")) {
              $("#time-"+field_name+"-"+delta).html(timecode(milliseconds));
            }
           
          }
          
        });
        
        
      }
      
      function stop(field_name, delta){
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-stop").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-play").show();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .record-again-btn").show();
        Recorder.stop();
      }
      
      function pause(field_name, delta){
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-pause").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-play").show();
        Recorder.stop();
      }
      
      function upload(field_name, delta) {
      
        //Remove any error messages
	    $("#edit-field-"+field_name+"-"+delta+"-wrapper .error").remove();
	    //Disable the button
	    $("#soundcloud-button-"+field_name+"-"+delta).attr('disabled', 'disabled');
        if($("#soundcloud-button-"+field_name+"-"+delta).val()=='Upload') {
	     //Upload button
         var path=Drupal.settings.basePath +"?q=audiorecorderfield_file_receive";
         Recorder.upload({
              url: path, 
              audioParam: "track[asset_data]",
              params: {
                "track[title]":   "recorder.js track test",
                "track[sharing]": "private"
              },
              success: function(fid){
               if (fid == null || fid == "") {
		         $("#soundcloud-button-"+field_name+"-"+delta).removeAttr("disabled");
		         $("#edit-field-"+field_name+"-"+delta+"-wrapper").append('<div class="messages error file-upload-js-error">Failed to submit the voice recording!</div>');
		       }
               else {
                 $.ajax({
					type: "GET",
					url: Drupal.settings.basePath +"?q=audiorecorderfield_file_preview",
					data: "fid=" + fid+"&field_name=" + field_name+"&delta=" +delta,
					dataType: 'json',
					success: SoundcloudPreview
				});
                 $("#edit-field-"+field_name+"-"+delta+"-fid").val(fid);
               }               
              }
            });
        }
        else {
          //$("#edit-field-"+field_name+"-"+delta+"-wrapper .filefield-file-info").remove();
	      $("#edit-field-"+field_name+"-"+delta+"-fid").val("");
	      $("#soundcloud-button-"+field_name+"-"+delta).removeAttr("disabled");
	      $("#soundcloud-button-"+field_name+"-"+delta).val('Upload');
          $.ajax({
					type: "GET",
					url: Drupal.settings.basePath +"?q=audiorecorderfield_recorder_reload",
					data: "field_name=" + field_name+"&delta=" +delta,
					dataType: 'json',
					success:  function (data) {
                      $("#audiorecorderfield-"+field_name+"-"+delta+"-wrapper").html(data.recorder);
                    }
				});
        }        
      }
      
      function record_again(field_name, delta) {
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-pause").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-play").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-stop").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .record-again-btn").hide();
        $("#soundcloud-"+field_name+"-"+delta+"-wrapper .soundcloud-record").show();
        $("#time-"+field_name+"-"+delta).html(timecode(0));
      }
      
function SoundcloudPreview(data){
  //Remove Upload button and add Remove button
  $("#soundcloud-button-"+data.field_name+"-"+data.delta).removeAttr("disabled");
  $("#soundcloud-button-"+data.field_name+"-"+data.delta).val('Remove');
  $("#soundcloud-"+data.field_name+"-"+data.delta+"-wrapper").remove();
  $("#soundcloud-button-"+data.field_name+"-"+data.delta).before(data.player);
}      

(function($){
    $.fn.extend({
        center: function () {
            return this.each(function() {
                var top = ($(window).height() - $(this).outerHeight()) / 2;
                var left = ($(window).width() - $(this).outerWidth()) / 2;
                $(this).css({position:'absolute', margin:0, top: (top > 0 ? top : 0)+'px', left: (left > 0 ? left : 0)+'px'});
            });
        }
    }); 
})(jQuery);
