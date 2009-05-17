<?php
// $Id$

/**
 * @file
 * Provide views data and handlers for the Facebook-style Statuses Tags module.
 */

/**
 * Implementation of hook_views_data().
 */
function facebook_status_tags_views_data() {
  $data['facebook_status_tags']['table']['group']  = t('Facebook-style Statuses');

  $data['facebook_status']['table']['join'] = array(
    'facebook_status_tags' => array(
      'left_field' => 'sid',
      'field' => 'sid',
    ),
  );
  $data['facebook_status_tags']['table']['join'] = array(
    'facebook_status' => array(
      'left_field' => 'sid',
      'field' => 'sid',
    ),
  );

  $data['facebook_status_tags']['sid'] = array(
    'title' => t('Status ID'),
    'help' => t('The ID of the status update.'),
  );

  $data['facebook_status_tags']['rid'] = array(
    'title' => t('Tag ID'),
    'help' => t('The Tag ID of the status - either a UID or Term ID depending on the reference type.'),
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

  $data['facebook_status_tags']['type'] = array(
    'title' => t('Tag type'),
    'help' => t('The type of tag - User or Taxonomy Term.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'facebook_status_views_handler_filter_string_type',
    ),
  );

  $data['facebook_status_tags']['name'] = array(
    'title' => t('Tag Name'),
    'help' => t('The name of the tag - a username or taxonomy term name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function facebook_status_tags_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'facebook_status'),
    ),
    'handlers' => array(
      'facebook_status_views_handler_filter_string_type' => array(
        'parent' => 'views_handler_filter_string',
      ),
    ),
  );
}