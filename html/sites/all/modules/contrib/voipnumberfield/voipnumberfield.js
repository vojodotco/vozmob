Drupal.behaviors.voipnumberfield = function (context) {
  //Hide conditional form fields
  voipnumberfield_hide_form_elements();

  //Check which radio button was selected to display appropriate fields
  if ($("#edit-voipnumberfield-choice-1").attr("checked")) {
    $("#edit-voipnumberfield-allowed-countries-wrapper").show();
  }
  else if ($("#edit-voipnumberfield-choice-2").attr("checked")) {
    $("#edit-voipnumberfield-show-code-wrapper").show();
  }

  /*Default country code radio button*/
  $("#edit-voipnumberfield-choice").change(function () {
    voipnumberfield_hide_form_elements();
  });

  /*Let user select from list radio button*/
  $("#edit-voipnumberfield-choice-1").change(function () {
    voipnumberfield_hide_form_elements();
    $("#edit-voipnumberfield-allowed-countries-wrapper").fadeIn();
  });

  /*Use default radio button*/
  $("#edit-voipnumberfield-choice-2").change(function () {
    voipnumberfield_hide_form_elements();
    $("#edit-voipnumberfield-show-code-wrapper").fadeIn();
  });

  //Make sure that default checkbox is selected only once per node
  $(".voipnumber-default").change(function () {
    if($(this).is(':checked')) {
      $(".voipnumber-default").attr("checked", false);
      $(this).attr("checked", true);
    }
  });
}

function voipnumberfield_hide_form_elements() {
  $("#edit-voipnumberfield-allowed-countries-wrapper").hide();
  $("#edit-voipnumberfield-show-code-wrapper").hide();
}
