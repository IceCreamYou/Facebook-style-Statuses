<?php

/**
 * @file
 *   Filters to allow only the latest status in Views.
 */

/**
 * Filter handler which requires the latest status.
 */
class facebook_status_views_handler_filter extends views_handler_filter_boolean_operator {

  function query() {
    if ($this->value) {
      $this->ensure_my_table();
      $this->query->add_where(0, db_prefix_tables("$this->table_alias.sid IN (SELECT MAX(sid) FROM {facebook_status} facebook_status GROUP BY facebook_status.uid)"));
    }
  }

}