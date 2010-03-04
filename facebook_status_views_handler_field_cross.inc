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
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, 'pid');
    $this->query->add_field($this->table_alias, 'uid');
    $this->add_additional_fields();
  }
  function pre_render($values) {
    $this->fbss_pid = $this->field_alias;
    //Obviously, not the right way to do this...
    $this->fbss_uid = str_replace('pid', 'uid', $this->field_alias);
  }
  function render($values) {
    $uid = $values->{$this->fbss_uid};
    $pid = $values->{$this->fbss_pid};
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