Drupal.behaviors.fbss_comments = function (context) {
  $(context).find('.fbss-comments-show-comment-form').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' + div').show();
    $(this).next().find('.fbss-comments-textarea').focus();
    return false;
  });
  $(context).find('.fbss-comments-show-comment-form-inner').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' + div').show();
    $(this).parents('form').find('.fbss-comments-textarea').focus();
    return false;
  });
  $(context).find('a.fbss-comments-show-comments').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' ~ div.fbss-comments-hide').show();
    return false;
  });
  $(context).find('.fbss-comments-submit').attr('disabled', true);
  $(context).find('.fbss-comments-textarea').keypress(function(key) {
    var th = $(this);
    setTimeout(function() {
      if (th.val().length > 0) {
        th.parents('form').find('input').attr('disabled', false);
      }
      else {
        th.parents('form').find('input').attr('disabled', true);
      }
    }, 10);
  });
  if ($.fn.autogrow) {
    // jQuery Autogrow plugin integration.
    // $('.fbss-comments-textarea').autogrow({expandTolerance: 2});
  }
}
