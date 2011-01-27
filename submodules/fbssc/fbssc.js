// $Id$
Drupal.behaviors.fbssc = function (context) {
  $('.fbssc_show_comment_form').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' + div').show();
    return false;
  });
  $('.fbssc_show_comment_form_inner').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' + div').show();
    return false;
  });
  $('a.fbssc_show_comments').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' ~ div.fbssc_hide').show();
    return false;
  });
}
