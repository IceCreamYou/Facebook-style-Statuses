// $Id$

== Summary ==

This module provides each user with a Facebook-style status.  This is a textfield where users can type what they're doing or thinking at that moment.  The user's status is available for display in several places.

Two permissions are provided: 'edit own facebook_status' and 'edit all facebook_status.'

First and foremost, this module adds a block to the site which displays:
  (A) The status of the user whose profile is being viewed or who created the node that is being viewed; or
  (B) The status of the current user.
If a user has permission to edit the status that is being displayed, a textfield will be available to update the status.  If enabled on the module's settings page, the form can be automatically shown and hidden when a user with permission to see the form clicks on the status text.  The default text that appears in the textfield is the user's latest status.

Secondly, a "Recent Status Updates" block is available.  This lists the latest status updates from all users on the site, but only shows one update per user.

Third, if the User Relationships module is enabled, a "UR Recent Status Updates" block is available.  This does the same thing as the "Recent Status Updates" block except that it only shows updates from users with whom the current user has a relationship.  The relationship type can be set on the module's settings page.

The 5.x version of the module also has support for the Activity module.  This gives developers more flexibility over how to display status updates than the standard blocks that come with the module, and it allows a more Facebook-style "mini-feed" if desired.

This module also provides what is known as "Facebook Mode."  Facebook Mode is enabled by default, and appends the relevant user's username to the front of the status.  That means users' statuses will be in the format "IceCreamYou is happy."  With Facebook Mode off, the module becomes a place for thought blurbs: for example, it could be used as a quote of the day of sorts.  This is especially useful on sites with a single user, like personal blogs.

At this time, submission of the status update form is not controlled by AJAX. As a temporary solution, check out the JavaScript Tools project and use the Ajax Submit submodule if you need this feature.

This module does not, and will not, sync Drupal status updates with Facebook's, and it is not affiliated with Facebook in any way.



== Development/API ==

This module's code is documented and styled in the Drupal Way, for any developers that would like to take a look.

For anyone who doesn't want to delve that deeply, this module provides simple functions you can use to take advantage of its functionality from anywhere you can use PHP.

(A) facebook_status_get_status($fbs_uid, $num_results)
    Returns an array of arrays. Each sub-array contains information about a single status update: the status itself, the timestamp, the user's UID, and the user's username. If no UID is passed in $fbs_uid, facebook_status figures out which one to use based on what page the function is called from. If the UID passed is -1, this function returns results for all users, but only includes one status update per user. If the UID passed is less than -1, this function returns all status updates. $num_results controls the number of status updates returned. If it is not specified, it defaults to 1; if it is passed as zero, there is no limit on the number of status updates returned.

(B) facebook_status_form_display()
    Prints the status submission form. You could use this, for instance, if you wanted to create a separate block for the user's status and for the status submission. This does not include an access check, so you should use it with user_access(). Uses the same length as the textfield in the default block.

(C) facebook_status_get_ur_status($ur_rtid, $number)
    Returns the latest status updates from users with whom the current user has a relationship. Only one status update is returned per user. If ur_rtid is not passed, this function uses the default relationship specified on the Facebook Status settings page. $number controls the number of statuses returned; if it is not passed, it defaults to the setting on the Facebook Status settings page.



== Installation ==

   1. Install this module as usual (FTP the files to sites/all/modules, enable at admin/build/modules).
   2. If you want, go to admin/settings/facebook_status to change some minor settings. The defaults should work for most people.
   3. Go to admin/user/access#facebook_status and set the permissions there. Note that anyone who can edit statuses (whether their own or everyone's) can also see everyone's status (because what fun is it if you can only see your own?). If you don't want this behavior you can use the functions (explained above) to build custom blocks so you have more fine-grained control.
   4. Go to admin/build/block and put the blocks in the regions you want them.
   5. Still on admin/build/block, configure the settings for each of the Facebook Status blocks. Set the blocks to only show up for users who you want to be able to see anyone's status.
   6. On the block configuration pages, scroll to the bottom and set where you want the blocks to show up. The most common configuration is to have them show up on user pages; to do this, choose the PHP option and enter the code below. Note that any time users can see their own status, they can also edit it, except in the Facebook Status Recent Updates block. Users will see their own status on their profile, on any nodes they created, and on any page that isn't a node or a user profile. If you don't want this behavior, use the functions (explained above) to create your own blocks.

<?php
  return arg(0) == 'user' && is_numeric(arg(1)) && !arg(2);
?>

In order to get a block to show up only on a user's own profile, use this code instead:

<?php
  global $user;
  return arg(0) == 'user' && is_numeric(arg(1)) && arg(1) == $user->uid && !arg(2);
?>



== Links ==

Visit the module page for more information and details about upcoming features.

Module Page: http://drupal.org/project/facebook_status
User Relationships: http://drupal.org/project/user_relationships
Activity: http://drupal.org/project/activity

Enable Module: http://example.com/?q=admin/build/modules
Enable Blocks: http://example.com/?q=admin/build/block
Settings Page: http://example.com/?q=admin/settings/facebook_status