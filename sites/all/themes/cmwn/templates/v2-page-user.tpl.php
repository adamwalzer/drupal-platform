<?php /* 1.4 */ ?>
<?php include 'page/header.tpl.php'; ?>
<?php 
  $uid = $user->uid;
  $current_user = true;
	if(arg(0) == 'user' && arg(1) != $user->uid && is_numeric(arg(1)) && arg(2) == 'edit'){
    $uid =  arg(1);
    $current_user = false;
  }
  
  $isedit = (arg(2) == 'edit');
?>
<div class="section-wrap">

	<?php print $messages; ?>

	<div id="v2">

		<div class="columns">

			<div class="column sidebar">
        <?php if(function_exists('v2_profiles_name_index')):?>
				<?php print v2_profiles_name_index($uid); ?>
				<?php endif;?>
				
				<?php if(function_exists('v2_profiles_avatars_index')):?>
				<?php print v2_profiles_avatars_index($uid); ?>
				<?php endif;?>

				<?php if(!$isedit):?>
  				
          <?php if(function_exists('v2_profiles_links_index')):?>
  				<?php print v2_profiles_links_index($uid); ?>
  				<?php endif;?>
  				
  				<?php if(function_exists('v2_profiles_friends_index')):?>
  				<?php print v2_profiles_friends_index($uid); ?>
  				<?php endif;?>
				
				<?php endif;?>

			</div>

			<div class="column content">
        <?php
          //tabs were specifically removed from this user page template, however, the authorization tab is needed for our cmwn services oauth api
          global $user;
          //if(user_access('administer users')){
          if($user->uid == 1 || in_array('School Administrator', $user->roles)){
            print $variables['tabs'];
          }
          
        ?>
				<?php print $content; ?>

			</div>

		</div>
    <?php if(function_exists('v2_profiles_feed_index')):?>
		<?php //print v2_profiles_feed_index($user->uid); ?>
		<?php endif;?>


	</div>

</div>

<?php if ($user->user_type == 'child' && !in_array('approved-child', $user->roles)) { ?>

	<div class="block modal" id="profile-pending-approval" style="display:none;">
		<div class="section title">
			<h1>Your profile awaits, BUT FIRST... get your parent's approval!</h1>
		</div>
		<div class="section cms">
			<p>We've sent them an email... can't wait to get you started!</p>
			<p>Check back soon!</p>
		</div>
		<div class="section buttons">
			<a class="button primary" href="/logout">Log Out</a>
		</div>
	</div>

<?php } ?>

<?php include 'page/footer.tpl.php'; ?>