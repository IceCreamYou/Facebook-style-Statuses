if (Drupal.jsEnabled) {
  $(document).ready(function () {
    $('div.facebook_status_block').find('div.facebook_status_form').hide().end().find('div.facebook_status_status').click(function() {
      $('div.facebook_status_form').slideToggle();
    });
  });
}