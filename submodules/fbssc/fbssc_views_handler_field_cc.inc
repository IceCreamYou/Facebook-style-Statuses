<?php
// $Id$

/**
 * @file
 *   Provides a "comment count" view field handler.
 */

/**
 * Implements the "comment count" field.
 */
class fbssc_views_handler_field_cc extends views_handler_field {
  function render($values) {
    $sid = $values->{$this->field_alias};
    $count = db_result(db_query("SELECT COUNT(cid) FROM {fbssc} WHERE sid = %d", $sid));
    return $count;
  }
}
