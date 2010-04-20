// $Id$
Drupal.behaviors.facebookStatus = function (context) {
  var $facebook_status_field = $('.facebook_status_update:first .facebook_status_text');
  var facebook_status_original_value = $facebook_status_field.val();
  var fbss_maxlen = Drupal.settings.facebook_status.maxlength;
  if (Drupal.settings.facebook_status.autofocus) {
     $facebook_status_field.focus();
     if ($facebook_status_field.val().length != 0) {
        fbss_print_remaining(fbss_maxlen - facebook_status_original_value.length, $facebook_status_field.parent().next());
     }
  }
  else {
    //Clear the status field the first time it's in focus if it hasn't been changed.
    $('.facebook_status_update_main .facebook_status_text').one('focus', function() {
      if ($(this).val() == facebook_status_original_value) {
        $(this).val('');
        fbss_print_remaining(fbss_maxlen, $(this).parent().next());
      }
    });
  }
  //Fix bad redirect destinations.
  $('.facebook_status_edit_delete a').each(function() {
    $(this).attr('href', $(this).attr('href').split('?')[0] +'?destination='+ escape(window.location.href));
  });
  $('a.facebook_status_conversation_link').each(function() {
    var loc = $(this).attr('href').split('?'), base = loc[0], query = '';
    if (loc[1]) {
      var q = loc[1].split('&');
      for (var i = 0; i < q.length; i++) {
        var item = q[i].split('='), param = item[0];
        if (i == 0) {
          query += '?';
        }
        else /*if (i != q.length-1)*/ {
          query += '&';
        }
        query += param +'=';
        if (param == 'destination') {
          query += escape(window.location.href);
        }
        else if (item[1]) {
          query += item[1];
        }
      }
    }
    $(this).attr('href', base + query);
  });
  //Restore original status text if the field is blank and the slider is clicked.
  $('.facebook_status_slider').click(function() {
    if ($(this).next().find('.facebook_status_text').val() == '') {
      $(this).next().find('.facebook_status_text').val(facebook_status_original_value);
      fbss_print_remaining(fbss_maxlen - facebook_status_original_value.length, $(this).next().next());
    }
  });
  //Count remaining characters.
  $('.facebook_status_update .facebook_status_text').keyup(function(fbss_key) {
    var fbss_remaining = fbss_maxlen - $(this).val().length;
    if (Drupal.settings.facebook_status.ttype == 'textfield' && fbss_remaining < 0) {
      fbss_remaining = 0;
    }
    fbss_print_remaining(fbss_remaining, $(this).parent().next());
  });
}
//Change remaining character count.
function fbss_print_remaining(fbss_remaining, where) {
  if (fbss_remaining >= 0) {
    where.html(Drupal.formatPlural(fbss_remaining, '1 character left', '@count characters left', {}));
  }
  else {
    where.html('<span class="facebook_status_negative">'+ Drupal.formatPlural(Math.abs(fbss_remaining), '-1 character left', '-@count characters left', {}) +'</span>');
  }
}