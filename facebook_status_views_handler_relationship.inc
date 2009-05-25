<?php
// $Id$

/**
 * @file
 *   A relationship handler which makes Users and FBSS work together nicely.
 */

/**
 * Joins the {facebook_status} and {user} tables.
 */
class facebook_status_views_handler_relationship extends views_handler_relationship {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function ensure_my_table() {
    if (!isset($this->table_alias)) {
      $join = $this->get_join();

      $this->table_alias = $this->query->add_table($this->table, $this->relationship, $join);
    }

    return $this->table_alias;
  }
}
