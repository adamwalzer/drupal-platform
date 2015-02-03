<?php /* 1.4 */ ?>
<?php
//redirect to add child form is session is set
if($data->user->user_type == 'parent') {
	if(isset($_SESSION['cptoken'])) {
		header("Location: /user/4848/children/add");
	}
}
?>
<?php if ($data->user->user_type == 'child') { ?>
	<?php print v2_profiles_flips_index($data->user->uid); ?>
	<?php print v2_profiles_whiteboard_index($data->user->uid); ?>

<?php } elseif($data->user->user_type == 'parent' || $data->user->user_type == 'verified-parent' || $data->user->user_type == 'teacher') { ?>

	<?php print v2_profiles_resource_center_index($data->user->uid); ?>
	<?php print v2_profiles_whiteboard_index($data->user->uid); ?>  
	<?php print v2_profiles_news_index($data->user->uid); ?>
	<?php //print v2_profiles_partners_index($data->user->uid); ?>
  <?php } else { ?>
  <?php print v2_profiles_partners_index($data->user->uid); ?>
  <?php }?>