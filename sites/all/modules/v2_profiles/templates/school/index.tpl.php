<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow school index">

	<div class="header">

		<div class="section">
			<?php if ($data->school): ?>
			<h2><?php print $data->school->title; ?></h2>
		<?php endif;?>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if ($data->school) { ?>
				<div class="my-school-image"><?php print theme('image', $data->school->field_image[0]['filepath']); ?></div>
			<?php } else { ?>
			<div class="empty">
				There are no schools.
			</div>
			<?php } ?>
		</div>

	</div>

</div>
