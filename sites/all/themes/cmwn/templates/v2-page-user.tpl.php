<?php /* 1.4 */ ?>

<?php include 'page/header.tpl.php'; ?>

<div class="section-wrap">

	<?php print $messages; ?>

	<div id="v2">

		<div class="columns">

			<div class="column sidebar">

				<?php print v2_profiles_name_index($user->uid); ?>
				<?php print v2_profiles_avatars_index($user->uid); ?>
				<?php print v2_profiles_links_index($user->uid); ?>
				<?php print v2_profiles_friends_index($user->uid); ?>

			</div>

			<div class="column content">

				<?php print $content; ?>

			</div>

		</div>

		<?php print v2_profiles_feed_index($user->uid); ?>

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