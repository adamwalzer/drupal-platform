<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow partners index">

	<div class="header">

		<div class="section">
			<h2>Partners</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="items">
				<?php foreach ($data->items as $item) { ?>
					<div class="item" style="background:url(<?= '/'.$item->field_icon[0]['filepath']?>) 0px 0px no-repeat;">
						<div class="title"><h2><?php print $item->title; ?></h2></div>
						<div class="excerpt"><p><?php print strip_tags($item->body); ?></p></div>
						<div class="more"><a href="/user/<?= $user->uid; ?>/partners/<?= $item->nid; ?>">Visit the partner's page</a></div>
					</div>
				<?php } ?>
			</div>
		</div>

	</div>

</div>