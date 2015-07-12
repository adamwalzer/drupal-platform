<?php /* 1.4 */ ?>

<div class="block profile">

	<?php print v2_profiles_avatars_index($data->user->uid); ?>

	<?php print $data->user->user_type == 'child'?v2_profiles_flips_index($data->user->uid):''; ?>
	<?php print ($data->user->user_type == 'teacher' || $data->user->user_type == 'parent')?v2_profiles_friends_browse($data->user->uid,4):''; ?>

</div>

<?php if ($data->relationship->approved == 1) { ?>

	<div class="block profile" style="clear:both;">

		<?php print $data->user->user_type == 'child'?v2_profiles_interests_index($data->user->uid):''; ?>

		<?php print $data->user->user_type == 'child'?v2_profiles_friends_browse($data->user->uid,4):''; ?>

	</div>

	<div class="block trigger1-target" style="clear:both;display:none;">

		<?php print v2_profiles_friends_browse($data->user->uid); ?>

	</div>

	<?php print v2_profiles_whiteboard_index($data->user->uid); ?>

<?php } ?>