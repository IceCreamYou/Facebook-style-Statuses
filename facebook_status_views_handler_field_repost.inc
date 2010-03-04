<?php
// $Id$

/**
 * @file
 *   Views handler for a "re-post" link.
 */

/**
 * Formats the "re-post" link.
 */
class facebook_status_views_handler_field_repost extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, 'sid');
    $this->query->add_field($this->table_alias, 'pid');
    $this->add_additional_fields();
  }
  function pre_render($values) {
    $this->fbss_sid = $this->field_alias;
    //Obviously, not the right way to do this...
    $this->fbss_pid = str_replace('sid', 'pid', $this->field_alias);
  }
  function render($values) {
    $pid = $values->{$this->fbss_pid};
    $sid = $values->{$this->fbss_sid};
    if ((user_access('edit own status') || user_access('edit all statuses')) && $pid != $GLOBALS['user']->uid) {
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $options = array(
        'attributes' => array('class' => 'facebook_status_conversation_link'),
        'query' => array('sid' => $sid, 'destination' => $_GET['q'])
      );
      return l(t('Re-post'), 'share-status', $options);
    }
  }
}