<?php
// $Id$

/**
 * @file
 *   Handling for the poster's picture in Views.
 */

/**
 * Shows the profile picture for the user who posted the status.
 */
class facebook_status_views_handler_field_poster_pic extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, 'pid');
    $this->add_additional_fields();
  }
  function render($values) {
    $account = _facebook_status_user_load($values->{$this->field_alias});
    return facebook_status_display_user_picture($account);
  }
}