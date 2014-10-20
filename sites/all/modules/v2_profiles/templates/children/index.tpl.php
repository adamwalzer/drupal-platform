<?php /* 1.4 */ ?>

<?php foreach ($data->items as $item) { ?>

	<div class="block profile">

		<?php print v2_profiles_avatars_index($item->uid); ?>

		<?php print v2_profiles_flips_index($item->uid); ?>

	</div>

	<?php if (!$data->teaser) { ?>

		<?php //print v2_profiles_whiteboard_index($item->uid); ?>

	<?php } ?>

<?php } ?>