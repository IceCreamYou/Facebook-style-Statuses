<?php
// $Id$

/**
 * @file
 *   Provides default Views for the Facebook-style Statuses module.
 */

/**
 * Implementation of hook_views_default_views().
 */
function facebook_status_views_default_views() {
  $view = new view;
  $view->name = 'facebook_status';
  $view->description = 'Facebook-style Statuses Profile';
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'users';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Statuses', 'default');
  $handler->override_option('fields', array(
    'pid_extra' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'pid_extra',
      'table' => 'facebook_status',
      'field' => 'pid_extra',
      'relationship' => 'none',
    ),
    'status' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'status',
      'table' => 'facebook_status',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status_time' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[pid_extra] [status] <em>[status_time]</em>',
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
        'button' => 'Override',
      ),
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
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1\'s Statuses',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'panel' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '$account = user_load(array(\'name\' => $argument));
            if ($account->uid) {
              $handler->argument = $account->name;
              return TRUE;
            }
            else {
              $account = user_load(array(\'uid\' => $argument));
              if ($account->uid) {
                $handler->argument = $account->name;
                return TRUE;
              }
            }
            return FALSE;',
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
    'pid_extra' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pid_extra',
      'table' => 'facebook_status',
      'field' => 'pid_extra',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'Statuses');
  $handler->override_option('empty', '<?php
    $account = user_load(array(\'uid\' => arg(1)));
    if (!$account->uid) {
      echo t(\'This user has no statuses yet.\');
      return;
    }
    $count = facebook_status_has_status(arg(1));
    if (!$count) {
      global $user;
      if ($user->uid == $account->uid) {
        echo t(\'You have no statuses yet.\');
      }
      else {
        echo t(\'@name has no statuses yet.\', array(\'@name\' => check_plain($account->name)));
      }
    }
    ?>');
  $handler->override_option('empty_format', '3');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', '1');
  $handler->override_option('use_more', 1);
  $handler->override_option('distinct', 0);
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
    'type' => 'tab',
    'title' => 'Statuses',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', 'Facebook-style Statuses Profile');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'facebook_status_recent';
  $view->description = 'Facebook-style Statuses Recent Status Updates';
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'facebook_status';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Latest Status', 'default');
  $handler->override_option('fields', array(
    'pid_extra' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'pid_extra',
      'table' => 'facebook_status',
      'field' => 'pid_extra',
      'relationship' => 'none',
    ),
    'status' => array(
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
        'text' => '[pid_extra] [status] <em>[status_time]</em>',
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
    'pid_extra' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pid_extra',
      'table' => 'facebook_status',
      'field' => 'pid_extra',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'Latest Status Updates');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 15);
  $handler->override_option('use_pager', '1');
  $handler->override_option('use_more', 1);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
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
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'statuses/recent');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Latest Status Updates',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Latest Status Updates',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('block_description', 'Facebook-style Statuses Latest Status Updates');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'facebook_status_cross_post';
  $view->description = 'Facebook-style Statuses Conversations';
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'facebook_status';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Conversation', 'default');
  $handler->override_option('fields', array(
    'pid_name' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'exclude' => 1,
      'id' => 'pid_name',
      'table' => 'facebook_status',
      'field' => 'pid_name',
      'relationship' => 'none',
    ),
    'status' => array(
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
        'text' => '[pid_name] [status] <em>[status_time]</em>',
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
    'uid' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Conversation',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 1,
      'not' => 0,
      'id' => 'uid',
      'table' => 'facebook_status',
      'field' => 'uid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '$names = explode(\',\', $argument);
      $uids = array();
      foreach ($names as $name) {
        if (!is_numeric($name)) {
          $account = user_load(array(\'name\' => $name));
        }
        else {
          $account = user_load(array(\'uid\' => $name));
        }
        if ($account->uid) {
          $uids[] = $account->uid;
        }
      }
      if (!empty($uids)) {
        global $user;
        if (count($uids) === 1 && $uids[0] != $user->uid) {
          $uids[1] = $user->uid;
        }
        $handler->argument = implode(\',\', $uids);
        return TRUE;
      }
      return FALSE;',
    ),
    'pid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Conversation',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 1,
      'not' => 0,
      'id' => 'pid',
      'table' => 'facebook_status',
      'field' => 'pid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '$arg = arg(2);
      $values = explode(\',\', $arg);
      global $user;
      if (count($values) === 1 && $values[0] != $user->uid && $values[0] != $user->name) {
        if (is_numeric($values[0])) {
          return $arg .\',\'. $user->uid;
        }
        else {
          return $arg .\',\'. $user->name;
        }
      }
      return $arg;',
      'validate_argument_node_type' => array(
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '$names = explode(\',\', $argument);
      $uids = array();
      foreach ($names as $name) {
        if (!is_numeric($name)) {
          $account = user_load(array(\'name\' => $name));
        }
        else {
          $account = user_load(array(\'uid\' => $name));
        }
        if ($account->uid) {
          $uids[] = $account->uid;
        }
      }
      if (!empty($uids)) {
        $handler->argument = implode(\',\', $uids);
        return TRUE;
      }
      return FALSE;',
    ),
  ));
  $handler->override_option('filters', array(
    'pid_extra_2' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pid_extra_2',
      'table' => 'facebook_status',
      'field' => 'pid_extra_2',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'Conversation');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
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
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'statuses/conversation');
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
  $views[$view->name] = $view;

  return $views;
}