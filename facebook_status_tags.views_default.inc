<?php
// $Id$

/**
 * @file
 *   Provides a default View for the Facebook-style Statuses Tags module.
 */

/**
 * Implementation of hook_views_default_views().
 */
function facebook_status_tags_views_default_views() {
  $view = new view;
  $view->name = 'facebook_status_tags';
  $view->description = 'Facebook-style Statuses Tags';
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'facebook_status';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = !module_exists('taxonomy');
  $handler = $view->new_display('default', 'Tag Reference', 'default');
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
        'text' => '[pid_extra] [status] [status_time]',
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
    'status_time' => array(
      'order' => 'DESC',
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
    ),
    'sid' => array(
      'order' => 'DESC',
      'id' => 'sid',
      'table' => 'facebook_status',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'has-specific-tag' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Statuses about #%1',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'taxonomy_term',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'ucfirst',
      'path_case' => 'none',
      'transform_dash' => 1,
      'facebook_status_tags_type' => array(
        'term' => 'term',
        'user' => 0,
      ),
      'id' => 'has-specific-tag',
      'table' => 'facebook_status',
      'field' => 'has-specific-tag',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'og' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 1,
        '4' => 0,
        '3' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'name',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
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
    'pid_extra_3' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pid_extra_3',
      'table' => 'facebook_status',
      'field' => 'pid_extra_3',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'Tags');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'pid_extra' => 'pid_extra',
      'status' => 'status',
      'status_time' => 'status_time',
    ),
    'info' => array(
      'pid_extra' => array(
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
  $handler->override_option('path', 'statuses/term');
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
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'facebook_status_rss');
  $handler->override_option('path', 'statuses/term/%/feed');
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
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array(
    'page_1' => 'page_1',
    'default' => 0,
  ));
  $handler->override_option('sitename_title', FALSE);
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'facebook_status_mentions';
  $view->description = 'Facebook-style Statuses Mentions';
  $view->tag = 'facebook_status';
  $view->view_php = '';
  $view->base_table = 'facebook_status';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'User Reference', 'default');
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
        'text' => '[pid_extra] [status] [status_time]',
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
    'status_time' => array(
      'order' => 'DESC',
      'id' => 'status_time',
      'table' => 'facebook_status',
      'field' => 'status_time',
      'relationship' => 'none',
    ),
    'sid' => array(
      'order' => 'DESC',
      'id' => 'sid',
      'table' => 'facebook_status',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'has-specific-tag-id' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Mentions',
      'breadcrumb' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 1,
      'not' => 0,
      'facebook_status_tags_type' => array(
        'user' => 'user',
        'term' => 0,
      ),
      'id' => 'has-specific-tag-id',
      'table' => 'facebook_status',
      'field' => 'has-specific-tag-id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'og' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '4' => 0,
        '1' => 0,
        '3' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '//If this view is overridden and then FBSS is disabled, it can
//cause a WSOD if these lines are not included here.
if (!function_exists(\'_facebook_status_user_load_by_name\')) {
  return;
}

$names = explode(\',\', $argument);
$uids = array();
foreach ($names as $name) {
  $account = _facebook_status_user_load_by_name($name);
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
    'pid_extra_3' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pid_extra_3',
      'table' => 'facebook_status',
      'field' => 'pid_extra_3',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all statuses',
  ));
  $handler->override_option('title', 'User Mentions');
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
  $handler->override_option('path', 'statuses/mentions');
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
  $handler->override_option('arguments', array(
    'has-specific-tag' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Mentions of %1',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'facebook_status_tags_type' => array(
        'user' => 'user',
        'term' => 0,
      ),
      'id' => 'has-specific-tag',
      'table' => 'facebook_status',
      'field' => 'has-specific-tag',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => 'return $GLOBALS[\'user\']->name; //The current user',
      'validate_argument_node_type' => array(
        'og' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '4' => 0,
        '1' => 0,
        '3' => 0,
        '2' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '//If this view is overridden and then FBSS is disabled, it can
//cause a WSOD if these lines are not included here.
if (!function_exists(\'_facebook_status_user_load\')) {
  return;
}

//If the argument is not present, get it from the UID in the URL instead.
if (arg(0) == \'user\' && !is_string($argument)) {
  $account = _facebook_status_user_load(arg(1));
  if ($account->uid) {
    $handler->argument = $account->name;
    return TRUE;
  }
}
else if (is_string($argument)) {
  $account = _facebook_status_user_load_by_name($argument);
  if ($account->uid) {
    return TRUE;
  }
}
return FALSE;',
    ),
  ));
  if (module_exists('php')) {
    $handler->override_option('footer', '<?php
    /*
      //If this view is overridden and then FBSS is disabled, it can
      //cause a WSOD if these lines are not included here.
      if (!function_exists(\'_facebook_status_user_load\')) {
        echo t(\'Facebook-style Statuses has been disabled.\');
        return;
      }

      //Adds a link to view your conversation with the user whose profile you are viewing.
      global $user;
      $account = _facebook_status_user_load(arg(1));
      if ($account->uid && $account->uid != $user->uid) {
        echo l(\'View mentions between you and \'. $account->name, \'statuses/conversation/\'. check_plain($account->name) .\',\'. check_plain($user->name));
      }
     */
    ?>');
    $handler->override_option('footer_format', '3');
    $handler->override_option('footer_empty', 0);
    $handler->override_option('empty', '<?php
    //If this view is overridden and then FBSS is disabled, it can
    //cause a WSOD if these lines are not included here.
    if (!function_exists(\'_facebook_status_user_load\')) {
      echo t(\'Facebook-style Statuses has been disabled.\');
      return;
    }

    if (arg(0) == \'user\') {
      $account = _facebook_status_user_load(arg(1));
      global $user;
      if ($user->uid == $account->uid) {
        echo t(\'No one has mentioned you yet.\');
      }
      else {
        echo t(\'No one has mentioned @name.\', array(\'@name\' => $account->name));
      }
    }
    ?>');
    $handler->override_option('empty_format', '3');
  }
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '0');
  $handler->override_option('pager_element', 11);
  $handler->override_option('use_more', 1);
  $handler->override_option('block_description', 'Facebook-style Statuses Conversation/Mentions');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  return $views;
}