<?php
// $Id$

/**
 * @file
 *   Rules integration.
 */

/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
function facebook_status_rules_event_info() {
  return array(
    'facebook_status_update' => array(
      'label' => t('User adds or updates a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'account' => array('type' => 'user', 'label' => t('The user who owns the status.')),
        'new_status' => array('type' => 'facebook_status', 'label' => t('The status.')),
      ),
    ),
    'facebook_status_delete' => array(
      'label' => t('Admin deletes a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'sid' => array('type' => 'facebook_status', 'label' => t('The status.')),
      ),
    ),
  );
}