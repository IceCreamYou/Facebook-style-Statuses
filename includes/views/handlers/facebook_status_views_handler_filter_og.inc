<?php

/**
 * @file
 *   Show group statuses in user streams.
 */

/**
 * Limits statuses to those in the current user's stream and in the current user's groups' streams.
 */
class facebook_status_views_handler_filter_og extends views_handler_filter {
  function query() {
    global $user;
    $this->ensure_my_table();
    $this->query->add_where(0, db_prefix_tables("
      ($this->table_alias.recipient = %d AND $this->table_alias.type = 'user') OR
      ($this->table_alias.type = 'og' AND $this->table_alias.recipient IN
        (SELECT nid FROM {og_uid} WHERE uid = %d AND is_active = 1)
      )
    "), $user->uid, $user->uid);
  }
}
