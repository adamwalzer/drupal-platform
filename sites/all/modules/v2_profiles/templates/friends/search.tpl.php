<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow friends browse">

	<div class="header">

		<div class="section">
			<h2>Search</h2>
		</div>

		<div class="section form">
			<form action="/user/<?php print $data->user->uid; ?>/friends/search" method="post">
				<input name="q" placeholder="Search Friends" type="text" />
				<button class="button" type="submit">Go!</button>
				<a class="button filter" href="#">Sort By Interest</a>
			</form>
		</div>

	</div>

	<div class="content">

		<div class="section search">
			<?php if (sizeof($data->items) > 0) { ?>
				<?php $cur_users_arr = array(); ?>
				<div class="items">
					<?php foreach ($data->items as $item) { ?>
						<?php
						if(!isset($cur_users_arr[$item->uid])) {
							$cur_users_arr[$item->uid] = 1;
							$total_earned_flips = 0;
							$flipstuff = v2_profiles_flips_query_all($item->uid);
							foreach($flipstuff as $key=>$val) {
								if($val->progress=='100') $total_earned_flips++;
							}
						?>

						<div class="item">
							<div class="image">
								<a href="<?php print $item->href; ?>"><img height="84" src="<?php print $item->src; ?>" width="84" /></a>
							</div>
							<div class="name">
								<a href="<?php print $item->href; ?>"><?php print $item->name; ?></a>
								<span><?php print (int)$total_earned_flips; ?> Flips Earned</span>
							</div>
							<div class="actions">
								<?php if (!$item->relationship) { ?>
									<a class="button green add" href="/user/<?php print $data->user->uid; ?>/friends/<?php print $item->uid; ?>/add">Add Friend</a>
								<?php } else if ($item->relationship && $item->relationship->approved == 0) { ?>
									<span class="button disabled requested">Request Sent</span>
								<?php } ?>
							</div>
						</div>
						<?php } ?>
					<?php } ?>
				</div>
			<?php } else { ?>
				<div class="empty">
					0 results found.
				</div>
			<?php } ?>
		</div>

	</div>

</div>

<div class="block friends modal interests" id="friends-interests" style="display:none;">

	<div class="section">
		<ul>
			<?php foreach ($data->interests as $item) { ?>
				<li class="<?php print $item->class; ?>"><a href="<?php print $item->href; ?>"><?php print $item->title; ?></a></li>
			<?php } ?>
		</ul>
	</div>

</div>