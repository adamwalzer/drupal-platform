<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') : ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php endif; ?>

