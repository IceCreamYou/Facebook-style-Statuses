<?php
// $Id$

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the status owner and status poster (if the status was posted elsewhere).
 * Also shows the user picture.
 */
class facebook_status_views_handler_field_cross_pic extends views_handler_field {
  function render($values) {
    if ($values->facebook_status_pid && $values->facebook_status_uid) {
      $uid = $values->facebook_status_uid;
      $pid = $values->facebook_status_pid;
    }
    else if ($values->facebook_status_sid) {
      $status = facebook_status_load($values->facebook_status_sid);
      $uid = $status->uid;
      $pid = $status->pid;
    }
    if (isset($uid) && $pid == $uid) {
      $account = user_load(array('uid' => $uid));
      return t('!picture !user', array('!picture' => facebook_status_display_user_picture($account), '!user' => theme('username', $account)));
    }
    else {
      $args = array('!poster' => theme('username', user_load(array('uid' => $pid))), '!owner' => theme('username', user_load(array('uid' => $uid))));
      $args['!poster-picture'] = facebook_status_display_user_picture(user_load(array('uid' => $pid)));
      $args['!owner-picture'] = facebook_status_display_user_picture(user_load(array('uid' => $uid)));
      return t('!poster-picture !poster &raquo; !owner-picture !owner', $args);
    }
  }
}

/**
 * Displays the user picture. Similar to theme('user_picture', $account) but
 * does not have problems with some themes floating the picture or wrapping it
 * in a div. However, this function is stylistically poor etiquette: the
 * technically correct way to do this would be to use CSS to format the output
 * of the original theme function, and the second-best way would be to write a
 * new theme function.
 */
function facebook_status_display_user_picture($account) {
  $picture = '';
  if (variable_get('user_pictures', 0)) {
    if (!empty($account->picture) && file_exists($account->picture)) {
      $picture = file_create_url($account->picture);
    }
    else if (variable_get('user_picture_default', '')) {
      $picture = variable_get('user_picture_default', '');
    }
    if ($picture) {
      $alt = t("@user's picture", array('@user' => $account->name));
      $picture = '<img src="'. check_url($picture) .'" alt="'. check_plain($alt) .'" />';
      if (!empty($account->uid) && user_access('access user profiles')) {
        $attributes = array('attributes' => array('title' => t('View user profile.'), 'class' => 'facebook_status_user_picture'), 'html' => TRUE);
        $picture = l($picture, 'user/'. $account->uid, $attributes);
      }
    }
  }
  return $picture;
}