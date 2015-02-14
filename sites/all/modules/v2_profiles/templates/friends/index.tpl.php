<?php /* 1.4 */ ?>

<?php if (in_array('can_make_friends', $user->roles)) { ?>

	<div class="block shadow friends index">

		<div class="header">

			<div class="section">
				<h2>Your Friends</h2>
			</div>

		</div>

		<div class="content">

			<div class="section search">
				<div class="items">
					<div class="item">
						<div class="image">
							<a href="/user/<?php print $user->uid; ?>/friends/search"><img src="/sites/all/themes/cmwn/assets/img/default/avatars/216.png" width="42" /></a>
						</div>
						<div class="name">
							<a href="/user/<?php print $user->uid; ?>/friends/search">Find More Friends!</a>
						</div>
					</div>
				</div>
			</div>

			<?php if (sizeof($data->items->friends) > 0) { ?>
				<div class="section">
					<div class="items">
						<?php foreach ($data->items->friends as $item) { ?>
							<div class="item">
								<div class="image">
									<a href="<?php print $item->href; ?>"><img src="<?php print $item->src; ?>" width="42" /></a>
								</div>
								<div class="name">
									<a href="<?php print $item->href; ?>"><?php print $item->name; ?></a>
								</div>
							</div>
						<?php } ?>
					</div>
				</div>
			<?php } ?>

		</div>

	</div>

	<?php if (sizeof($data->items->all) > 0) { ?>

		<div class="block shadow friends index">

			<div class="header">

				<div class="section">
					<h2>You May Know</h2>
				</div>

			</div>

			<div class="content">

				<div class="section">
					<div class="items">
						<?php foreach ($data->items->all as $item) { ?>
							<div class="item">
								<div class="image">
									<a href="<?php print $item->href; ?>"><img src="<?php print $item->src; ?>" width="42" /></a>
								</div>
								<div class="name">
									<a href="<?php print $item->href; ?>"><?php print $item->name; ?></a>
								</div>
							</div>
						<?php } ?>
					</div>
				</div>

			</div>

		</div>

	<?php } ?>

<?php } ?>