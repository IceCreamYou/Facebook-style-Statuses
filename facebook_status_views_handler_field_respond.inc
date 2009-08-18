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
    if ($values->facebook_status_pid && $values->uid && $values->facebook_status_pid != $values->uid && user_access('post on all profiles')) {
      $owner = user_load(array('uid' => $values->uid));
      $poster = user_load(array('uid' => $values->facebook_status_pid));
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $options = array('attributes' => array('class' => 'facebook_status_conversation_link'));
      $title = t('View conversation');
      if ($owner->uid == $user->uid) {
        $title = t('Respond');
      }
      return l($title, 'statuses/conversation/'. check_plain($poster->name) .','. check_plain($owner->name), $options);
    }
  }
}