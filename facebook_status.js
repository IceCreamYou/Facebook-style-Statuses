// $Id$
Drupal.behaviors.facebookStatus = function (context) {
  $facebook_status_field = $('#facebook_status_update #edit-fbss-status');
  $facebook_status_chars = $('#facebook_status_update #facebook_status_chars');
  facebook_status_original_value = $facebook_status_field.val();
  fbss_maxlen = Drupal.settings.facebook_status.maxlength;
  if (Drupal.settings.facebook_status.autofocus) {
     $facebook_status_field.focus();
     if ($facebook_status_field.val().length != 0) {
        fbss_print_remaining(fbss_maxlen - $facebook_status_field.val().length);
     }
  }
  else {
    //Clear the status field the first time it's in focus if it hasn't been changed.
    $('#facebook-status-box #edit-fbss-status').one('focus', function() {
      facebook_status_value = $facebook_status_field.val();
      if (facebook_status_value == facebook_status_original_value) {
        $facebook_status_field.val('');
        fbss_print_remaining(fbss_maxlen);
      }
    });
  }
  //Restore original status text if the field is blank and the slider is clicked.
  $('#facebook_status_slider').click(function() {
    facebook_status_value = $facebook_status_field.val();
    if (facebook_status_value == '') {
      $facebook_status_field.val(facebook_status_original_value);
      fbss_print_remaining(fbss_maxlen - facebook_status_original_value.length);
    }
  });
  //Count remaining characters.
  $facebook_status_field.keyup(function(fbss_key) {
    fbss_remaining = fbss_maxlen - $facebook_status_field.val().length;
    if (Drupal.settings.facebook_status.ttype == 'textfield' && fbss_remaining < 0) {
      fbss_remaining = 0;
    }
    fbss_print_remaining(fbss_remaining);
  });
}
//Change remaining character count.
function fbss_print_remaining(fbss_remaining) {
  var fbss_translations = new Array();
  fbss_translations['%chars'] = fbss_remaining;
  if (fbss_remaining >= 0) {
    $facebook_status_chars.html(Drupal.t('%chars characters remaining', fbss_translations));
  }
  else {
    fbss_newval = '<span class="facebook_status_negative">'+ Drupal.t('%chars characters remaining', fbss_translations) +'</span>';
    $facebook_status_chars.html(fbss_newval);
  }
}