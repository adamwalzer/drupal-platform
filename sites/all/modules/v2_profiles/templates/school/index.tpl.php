<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow school index">

	<div class="header">

		<div class="section">
			<h2>School</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if ($data->school) { ?>
				<p><?php print $data->school->title; ?></p>
			<?php } else { ?>
			<div class="empty">
				There are no schools.
			</div>
			<?php } ?>
		</div>

	</div>

</div>