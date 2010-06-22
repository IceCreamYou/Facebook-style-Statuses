<?php
// $Id$

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the status owner and status poster (if the status was posted elsewhere).
 */
class facebook_status_views_handler_field_cross extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
  }
  function render($values) {
    $uid = $values->{$this->aliases['uid']};
    $pid = $values->{$this->field_alias};
    if (isset($uid) && $pid == $uid) {
      return theme('username', _facebook_status_user_load($uid));
    }
    else {
      $args = array('!poster' => theme('username', _facebook_status_user_load($pid)),
        '!owner' => theme('username', _facebook_status_user_load($uid)));
      return t('!poster &raquo; !owner', $args);
    }
  }
}