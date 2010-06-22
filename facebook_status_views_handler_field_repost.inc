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
  function construct() {
    parent::construct();
    $this->additional_fields['pid'] = 'pid';
  }
  function render($values) {
    if ((user_access('edit own status') || user_access('edit all statuses')) && $values->{$this->aliases['pid']} != $GLOBALS['user']->uid) {
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $options = array(
        'attributes' => array('class' => 'facebook_status_conversation_link'),
        'query' => array('sid' => $values->{$this->field_alias}, 'destination' => $_GET['q'])
      );
      return l(t('Re-post'), 'share-status', $options);
    }
  }
}