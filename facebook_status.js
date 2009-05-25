// $Id$

Drupal.behaviors.facebookStatus = function (context) {
  facebook_status_count = 1;
  facebook_status_original_value = $('div#facebook_status_update').find('#edit-status').val();
  //Clear the status field the first time it's in focus if it hasn't been changed.
  $('div#facebook_status_update').find('#edit-status').focus(function() {
    facebook_status_value = $('div#facebook_status_update').find('#edit-status').val();
    if (facebook_status_count == 1 && facebook_status_value == facebook_status_original_value) {
      $('div#facebook_status_update').find('#edit-status').val("");
      facebook_status_count = 0;
    }
  });
  //Put the original status text back in the field if it is blank and the slider is clicked.
  $('div#facebook_status_update').find('#facebook_status_slider').click(function() {
    facebook_status_value = $('div#facebook_status_update').find('#edit-status').val();
    if (facebook_status_count != 2 && facebook_status_value == '') {
      facebook_status_count = 2;
      $('div#facebook_status_update').find('#edit-status').val(facebook_status_original_value);
    }
  });
  //Show an indicator of the remaining characters.
  $('div#facebook_status_update').find('#edit-status').keypress(function(fbss_key) {
    //The following logic corrects counting errors.
    fbss_remaining = Drupal.settings.facebook_status.maxlength - $('div#facebook_status_update').find('#edit-status').val().length - 1;
    if (fbss_key.which == 8 && fbss_remaining + 1 < Drupal.settings.facebook_status.maxlength) {
      fbss_remaining += 2;
    }
    else if (fbss_key.which == 8 && isNaN($('div#facebook_status_update').find('#edit-status').val().charCodeAt())) {
      fbss_remaining++;
    }
    else if (fbss_key.which != 8 && Drupal.settings.facebook_status.ttype == 'textfield' && fbss_remaining < 0) {
      fbss_remaining = 0;
    }
    //Outputs translated remaining characters.
    var fbss_translations = new Array();
    fbss_translations['%chars'] = fbss_remaining;
    if (fbss_remaining >= 0) {
      $('div#facebook_status_update').find('#facebook_status_chars').html(Drupal.t('(%chars)', fbss_translations));
    }
    else {
      fbss_newval = '<span class="facebook_status_negative">'+ Drupal.t('(%chars)', fbss_translations) +'</span>';
      $('div#facebook_status_update').find('#facebook_status_chars').html(fbss_newval);
    }
  });
}