Drupal.behaviors.voipvoice = function (context) {
  $('.voipvoice-uploaders').find('div.source-upload').css('display', 'none');
  $(".sources-list a").click(function(){
		$Element = $(this).parents('div.voipvoice-uploaders');
        var fileFieldSourceClass = this.className.match(/source-[0-9a-z]+/i)[0];
        $Element.find('div.source').not('div.' + fileFieldSourceClass).css('display', 'none');
      $Element.find('div.' + fileFieldSourceClass).css('display', '');
  });
}