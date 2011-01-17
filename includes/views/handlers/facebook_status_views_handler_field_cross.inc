<?php
// $Id$

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the sender and recipient (if the status was posted elsewhere).
 */
class facebook_status_views_handler_field_cross extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['recipient'] = 'recipient';
    $this->additional_fields['type'] = 'type';
  }
  function render($values) {
    $type = $values->{$this->aliases['type']};
    $recipient_id = $values->{$this->aliases['recipient']};
    $sender_id = $values->{$this->field_alias};
    if ($sender_id == $recipient_id && $type == 'user') {
      return theme('username', _facebook_status_user_load($sender_id));
    }
    else {
      $args = array(
        '!sender' => theme('username', _facebook_status_user_load($sender_id)),
        '!recipient' => theme('username', _facebook_status_user_load($recipient_id))
      );
      return t('!sender &raquo; !recipient', $args);
    }
  }
}
