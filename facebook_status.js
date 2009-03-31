if (Drupal.jsEnabled) {
  $(document).ready(function () {
    facebook_status_count = 1;
    facebook_status_original_value = $('div#facebook_status_update').find('input#edit-status').val();
    //Show or hide status form.
    $('div#facebook_status_update').find('span.facebook_status_hide').hide().end().find('a.facebook_status_slide').click(function() {
      $('span.facebook_status_hide').slideToggle();
    });
    $('div#facebook_status_update').find('input#edit-status').focus(function() {
      facebook_status_form_clear();
    });
  });
  function facebook_status_form_clear() {
    facebook_status_value = $('div#facebook_status_update').find('input#edit-status').val();
    //Clear field on focus unless new text has been entered.
    if (facebook_status_count == 1) {
      facebook_status_value = "";
      $('div#facebook_status_update').find('input#edit-status').val(facebook_status_value);
    }
    $('div#facebook_status_update').find('input#edit-status').keypress(function() {
      facebook_status_count = 0;
    });
    //Set to original value if field is empty and the textfield is closed.
    $('div#facebook_status_update').find('a.facebook_status_slide').click(function() {
      if ($('div#facebook_status_update').find('input#edit-status').val() == "") {
        facebook_status_value = facebook_status_original_value;
        $('div#facebook_status_update').find('input#edit-status').val(facebook_status_value);
      }
    });
  }
}