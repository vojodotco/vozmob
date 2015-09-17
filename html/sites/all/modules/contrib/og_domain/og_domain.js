
// TODO put this somewhere else

$(function(){
   $("#edit-sitename-override:checked").parent().parent().parent().children('#edit-sitename-override-custom-wrapper').hide();
   $("#edit-sitename-override").click(function(){
       $("#edit-sitename-override-custom-wrapper").toggle();
   });
});