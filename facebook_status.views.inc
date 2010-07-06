<?php
// $Id$

/**
 * @file
 * Provide views data and handlers for the Facebook-style Statuses module.
 */

/**
 * Implementation of hook_views_data().
 */
function facebook_status_views_data() {
  //Basic table information.
  $data['facebook_status']['table']['group']  = t('Facebook-style Statuses');
  $data['facebook_status']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
      'type' => 'INNER',
    ),
  );
  $data['users']['table']['join'] = array(
    'facebook_status' => array(
      'left_field' => 'uid',
      'field' => 'uid',
      'type' => 'INNER',
    ),
  );

  //Advertise this table as a possible base table.
  $data['facebook_status']['table']['base'] = array(
    'field' => 'sid',
    'title' => t('Facebook-style Statuses Updates'),
    'help' => t('Stores status updates.'),
    'weight' => 10,
  );
  /*
  $data['facebook_status']['users'] = array(
    'group' => t('Facebook-style Statuses'),
    'relationship' => array(
      'title' => t('Users'),
      'label' => t('Users'),
      'help' => t('Add a relationship to gain access to information related to the users who submitted the relevant statuses.'),
      'relationship table' => 'users',
      'relationship field' => 'uid',
      'base' => 'facebook_status',
      'field' => 'uid',
      'type' => 'INNER',
      'handler' => 'views_handler_relationship',
    ),
  );
   */

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

  //Alias for Status ID to extend its use.
  $data['facebook_status']['sid_extra'] = array(
    'title' => t('Last Status per User'),
    'help' => t('Show only the last status update for each user.'),
    'filter' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_views_handler_filter',
      'label' => t('Last Status per User'),
    ),
  );
  $data['facebook_status']['edit'] = array(
    'title' => t('Edit'),
    'help' => t('Shows a link to edit the status to users with permission to see it.'),
    'field' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_views_handler_field_edit',
      'click sortable' => FALSE,
    ),
  );
  $data['facebook_status']['delete'] = array(
    'title' => t('Delete'),
    'help' => t('Shows a link to delete the status to users with permission to see it.'),
    'field' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_views_handler_field_delete',
      'click sortable' => FALSE,
    ),
  );
  $data['facebook_status']['repost'] = array(
    'title' => t('Re-post'),
    'help' => t('Shows a link to re-post a status.'),
    'field' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_views_handler_field_repost',
      'click sortable' => FALSE,
    ),
  );

  //Declares the Owner UID column.
  $data['facebook_status']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The User ID of the owner of the status (if the status is from one user to another, this is the recipient).'),
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

  //Declares the Poster UID column.
  $data['facebook_status']['pid'] = array(
    'title' => t('Poster UID'),
    'help' => t('The User ID of the poster of the status.'),
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

  //Alias for Poster UID to use the name.
  $data['facebook_status']['pid_name'] = array(
    'title' => t('Poster Name'),
    'help' => t('The name of the user who posted the status.'),
    'field' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_field_poster',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'field' => 'pid',
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'field' => 'pid',
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'field' => 'pid',
      'handler' => 'views_handler_argument_user_uid',
    ),
  );
  //Alias for poster picture.
  $data['facebook_status']['pid_pic'] = array(
    'title' => t('Poster picture'),
    'help' => t('The picture of the user who posted the status.'),
    'field' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_field_poster_pic',
      'click sortable' => FALSE,
    ),
  );

  //Alias for extras for the poster.
  $data['facebook_status']['pid_extra'] = array(
    'title' => t('Usernames (context-aware)'),
    'help' => t('The themed username(s) of either the owner or the sender and recipient of the status, depending on the context.'),
    'field' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_field_cross',
      'click sortable' => FALSE,
      'label' => t('Users'),
    ),
  );
  $data['facebook_status']['pid_extra_2'] = array(
    'title' => t('Not own statuses'),
    'help' => t("Do not show statuses posted to one's own profile."),
    'filter' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_filter_not_own',
      'label' => t("Restrict to others' statuses"),
    ),
  );
  //This is slightly different than, but could probably be combined with, pid_extra_2.
  $data['facebook_status']['pid_extra_3'] = array(
    'title' => t('Only own statuses'),
    'help' => t("Only show statuses posted to one's own profile."),
    'filter' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_filter_own',
      'label' => t('Restrict to own statuses'),
    ),
  );
  $data['facebook_status']['crosspost_users_pics'] = array(
    'title' => t('Users with Pictures'),
    'help' => t('The themed username(s) and pictures of either the owner or the sender and recipient of the status, depending on the context.'),
    'field' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_field_cross_pic',
      'click sortable' => FALSE,
      'label' => t('Users with Pictures'),
    ),
  );
  $data['facebook_status']['respond'] = array(
    'title' => t('Respond link'),
    'help' => t('Links to view the conversation or respond to it when appropriate.'),
    'field' => array(
      'field' => 'pid',
      'handler' => 'facebook_status_views_handler_field_respond',
      'click sortable' => FALSE,
      'label' => t('Respond to conversation'),
    ),
  );

  //Declares the status message timestamp column.
  $data['facebook_status']['status_time'] = array(
    'title' => t('Created time'),
    'help' => t('The time the status message was posted.'),
    'field' => array(
      'handler' => 'facebook_status_views_handler_field_created',
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
      'handler' => 'facebook_status_views_handler_field_status',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['activity']['activity-fbss-poster-pic'] = array(
    'title' => t('Poster picture'),
    'help' => t("The picture of the user who took action (normally the same as Users: Picture, but shows the poster's picture for status messages)."),
    'field' => array(
      'field' => 'uid',
      'handler' => 'facebook_status_views_handler_field_poster_pic_activity',
      'click sortable' => FALSE,
    ),
  );

  if (module_exists('flag')) {
    $data['facebook_status']['user-flag-plus-current'] = array(
      'title' => t('Content from flagged users or the current user'),
      'filter' => array(
        'field' => 'pid',
        'handler' => 'facebook_status_views_handler_filter_flagged_user',
      ),
    );
    $data['facebook_status']['user-flag-plus-arg'] = array(
      'title' => t('Content from flagged users or the argument user'),
      'argument' => array(
        'field' => 'pid',
        'handler' => 'facebook_status_views_handler_argument_flagged_user',
      ),
    );
  }

  return $data;
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
      'facebook_status_views_handler_argument_flagged_user' => array(
        'parent' => 'views_handler_argument',
      ),
      'facebook_status_views_handler_field_created' => array(
        'parent' => 'views_handler_field_date',
      ),
      'facebook_status_views_handler_field_cross' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_cross_pic' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_delete' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_edit' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_poster' => array(
        'parent' => 'views_handler_field_user',
      ),
      'facebook_status_views_handler_field_poster_pic' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_poster_pic_activity' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_repost' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_respond' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_field_status' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_views_handler_filter' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'facebook_status_views_handler_filter_flagged_user' => array(
        'parent' => 'views_handler_filter',
      ),
      'facebook_status_views_handler_filter_not_own' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'facebook_status_views_handler_filter_own' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function facebook_status_views_plugins() {
  return array(
    'row' => array(
      'facebook_status_rss' => array(
        'title' => t('RSS items'),
        'help' => t('Displays statuses as RSS items.'),
        'handler' => 'facebook_status_views_plugin_row_rss',
        'parent' => 'fields',
        'path' => drupal_get_path('module', 'facebook_status'),
        'theme' => 'views_view_row_rss',
        'base' => array('facebook_status'),
        'uses fields' => FALSE,
        'uses options' => FALSE,
        'type' => 'feed',
      ),
    )
  );
}