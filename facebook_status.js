if (Drupal.jsEnabled) {
  $(document).ready(function () {
    facebook_status_count = 1;
    facebook_status_original_value = $('div.facebook_status_block').find('input#edit-name').val();
    //Show or hide status form.
    $('div.facebook_status_block').find('div.facebook_status_form').hide().end().find('div.facebook_status_status').click(function() {
      $('div.facebook_status_form').slideToggle();
    });
    $('div.facebook_status_block').find('input#edit-name').focus(function() {
      facebook_status_form_clear();
    });
  });
  function facebook_status_form_clear() {
    facebook_status_value = $('div.facebook_status_block').find('input#edit-name').val();
    //Clear field on focus unless new text has been entered.
    if (facebook_status_count == 1) {
      facebook_status_value = "";
      $('div.facebook_status_block').find('input#edit-name').val(facebook_status_value);
    }
    $('div.facebook_status_block').find('input#edit-name').keypress(function() {
      facebook_status_count = 0;
    });
    //Set to original value if field is empty and the textfield is closed.
    $('div.facebook_status_block').find('div.facebook_status_status').click(function() {
      if ($('div.facebook_status_block').find('input#edit-name').val() == "") {
        facebook_status_value = facebook_status_original_value;
        $('div.facebook_status_block').find('input#edit-name').val(facebook_status_value);
      }
    });
  }
}