<?php
// $Id$

/**
 * @file
 *   Filters to allow only the latest status in Views.
 */

/**
 * Filter handler which requires the latest status.
 */
class facebook_status_views_handler_filter extends views_handler_filter_boolean_operator {
  function construct() {
    $this->definition['type'] = 'yes-no';
    $this->definition['label'] = t('Show Latest Status Update Only (per User)');
    $this->value_value = $this->definition['label'];
    parent::construct();
  }

  function query() {
    if ($this->value) {
      $this->ensure_my_table();
      $subquery = "(SELECT MAX(sid) FROM {facebook_status} WHERE uid = pid GROUP BY uid)";
      $this->query->add_where(0, db_prefix_tables("$this->table_alias.sid IN ". $subquery));
    }
  }
}