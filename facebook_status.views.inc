<?php
// $Id$

/**
 * @file
 * Provide views data and handlers for the Facebook-style Statuses module.
 */

/**
 * @defgroup views_facebook_status_module facebook_status.module handlers
 *
 * Includes the ability to create views of just the facebook_status table.
 * @{
 */

/**
 * Implementation of hook_views_data().
 */
function facebook_status_views_data() {
  //Basic table information.

  $data['facebook_status']['table']['group']  = t('Facebook-style Statuses');

  $data['users']['table']['join'] = array(
    'facebook_status' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['facebook_status']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  //Advertise this table as a possible base table.
  $data['facebook_status']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Facebook-style Statuses Updates'),
    'help' => t('Stores status updates.'),
    'weight' => 10,
  );

  //Declares the Status ID column.
  $data['facebook_status']['sid'] = array(
    'title' => t('Status ID'),
    'help' => t('The ID of the status update.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  //Declares the User ID column.
  $data['facebook_status']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The User ID of the owner of the status.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  //Declares the status message timestamp column.
  $data['facebook_status']['status_time'] = array(
    'title' => t('Created time'),
    'help' => t('The time the status message was posted.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  //Declares the status text column.
  $data['facebook_status']['status'] = array(
    'title' => t('Status text'),
    'help' => t('The text of the status update.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function facebook_status_views_data_alter(&$data) {
  $data['facebook_status']['users'] = array(
    'group' => t('Facebook-style Statuses'),
    'relationship' => array(
      'title' => t('Users'),
      'label' => t('Users'),
      'help' => t('Add a relationship to gain access to information related to the users who submitted the relevant statuses.'),
      'relationship table' => 'facebook_status',
      'relationship field' => 'uid',
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'facebook_status_views_handler_relationship',
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function facebook_status_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'facebook_status'),
    ),
    'handlers' => array(
      'facebook_status_views_handler_relationship' => array(
        'parent' => 'views_handler_relationship',
      ),
    ),
  );
}