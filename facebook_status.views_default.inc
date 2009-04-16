<?php
// $Id$

/**
 * @file
 *   Provides a default View for the Facebook-style Statuses module.
 */

/**
 * Implementation of hook_views_default_views().
 */
function facebook_status_views_default_views() {
  $view = new view;
  $view->name = 'facebook_status';
  $view->description = t('Facebook-style Statuses');
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'users';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Statuses', 'default');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => t('Status'),
      'alter' => array(
        'alter_text' => 1,
        'text' => '[name] [status]',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status_time' => array(
      'label' => t('Posted'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'time ago',
      'custom_date_format' => '1',
      'exclude' => 0,
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'sid' => array(
      'order' => 'DESC',
      'id' => 'sid',
      'table' => 'facebook_status',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'name' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => t("%1's Statuses"),
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'image' => 0,
        'feed' => 0,
        'news' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '3' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'tid',
      'user_argument_type' => 'either',
      'restrict_user_roles' => 0,
      'user_roles' => array(
        '2' => '2',
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '!=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'case' => 1,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', t('Statuses'));
  $handler->override_option('empty', t('No relevant statuses were found.'));
  $handler->override_option('empty_format', '5');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', '1');
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'uid' => 'uid',
      'status' => 'status',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'uid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'user/%/status');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => t('Status'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '[name] [status]',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '25',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'status_time' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[name] [status] <em>[status_time]</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'time ago',
      'custom_date_format' => '1',
      'exclude' => 0,
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '0');
  $handler->override_option('use_more', 1);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array());
  $handler->override_option('row_options', array(
    'inline' => array(
      'name' => 'name',
      'status' => 'status',
    ),
    'separator' => ' ',
  ));
  $handler->override_option('block_description', t('Facebook-style Statuses User List'));
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'facebook_status_recent';
  $view->description = t('Facebook-style Statuses Last Status Update');
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'facebook_status';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Latest Status', 'default');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => t('Name'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => t('Status text'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'status_time' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[name] [status] <em>[status_time]</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'sid' => array(
      'order' => 'DESC',
      'id' => 'sid',
      'table' => 'facebook_status',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'sid_extra' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid_extra',
      'table' => 'facebook_status',
      'field' => 'sid_extra',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'Latest Status Updates');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'type' => 'ul',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 0,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'status' => 'status',
      'status_time' => 'status_time',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('path', 'recent_statuses');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => t('Name'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => t('Status text'),
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '72',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => t('Use default'),
      ),
    ),
    'status_time' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[name] [status] <em>[status_time]</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'time ago',
      'custom_date_format' => '1',
      'exclude' => 0,
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
      'override' => array(
        'button' => t('Use default'),
      ),
    ),
  ));
  $handler->override_option('block_description', t('Facebook-style Statuses Latest Status Updates'));
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  return $views;
}