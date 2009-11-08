<?php
// $Id$

/**
 * @file
 *   Views handler for a "view conversation" link.
 */

/**
 * Formats the "view conversation" link.
 */
class facebook_status_views_handler_field_respond extends views_handler_field {
  function render($values) {
    global $user;
    if ($values->facebook_status_pid && $values->uid) {
      $owner = user_load(array('uid' => $values->uid));
      $poster = user_load(array('uid' => $values->facebook_status_pid));
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $options = array('attributes' => array('class' => 'facebook_status_conversation_link'));
      if ($owner->uid != $poster->uid && user_access('post on all profiles')) {
        $title = t('View conversation');
        if ($owner->uid == $user->uid) {
          $title = t('Reply');
        }
        return l($title, 'statuses/conversation/'. check_plain($poster->name) .','. check_plain($owner->name), $options);
      }
      elseif ((user_access('edit own status') || user_access('edit all statuses')) && $owner->uid == $poster->uid && $poster->uid != $user->uid) {
        $s = '@'. $poster->name .' ';
        //Properly reference tags with word-break characters in them.
        if (preg_match('/.+\b.+/', $poster->name)) {
          $s = '[@'. $poster->name .'] ';
        }
        if (variable_get('facebook_status_reply_type', 'at') == 'at') {
          //Evidently url() sanitizes query strings itself, so we don't have to use check_plain() here.
          $options['query'] = array('s' => $s, 'rsid' => $values->facebook_status_sid, 'destination' => $_GET['q']);
          return l(t('Respond'), 'share-status', $options);
        }
        return l(t('Respond'), 'statuses/conversation/'. check_plain($poster->name) .','. check_plain($user->name), $options);
      }
    }
  }
}