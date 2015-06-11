<?php /* 1.4 */ ?>

<?php if ($user->uid === $data->user->uid && $data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow friends browse">

	<div class="header">

		<div class="section">
			<h2>Friends<?php print ($data->limit == 0)? ': '.sizeof($data->items->friends) : ''; ?></h2>
		</div>

		<?php if ($data->limit > 0) { ?>
			<div class="section form">
				<a class="button trigger1-source" href="#">View All</a>
			</div>
			<script>
				$(function(){
					$('.trigger1-source').bind('click',function(){
						$('.block.profile').eq(1).toggle();
						$('.block.whiteboard').toggle();
						$('.trigger1-target').toggle();
						if($('.block.whiteboard:visible').length > 0){
							$('.trigger1-source').html('View All');
						}else{
							$('.trigger1-source').html('Show Less');
						}
						return false;
					});
				});
			</script>
		<?php } ?>

		<?php if ($user->uid === $data->user->uid && $user->user_type == 'child') { ?>
			<div class="section form">
				<form action="/user/<?php print $data->user->uid; ?>/friends/search" method="post">
					<input name="q" placeholder="Search Friends" type="text" />
					<button class="button" type="submit">Go!</button>
				</form>
			</div>
		<?php } ?>

	</div>

	<div class="content">

		<?php if ($data->user->uid == $user->uid) { ?>
			<?php if (sizeof($data->items->requests) > 0) { ?>
				<div class="section search">
					<div class="items">
						<?php foreach ($data->items->requests as $item) { ?>
							<?php
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
									<a class="button view" href="/user/<?php print $data->user->uid; ?>/friends/<?php print $item->uid; ?>">View Profile</a>
									<a class="button green approve" href="/user/<?php print $data->user->uid; ?>/friends/<?php print $item->uid; ?>/approve">Add Friend</a>
									<a class="button red ignore" href="/user/<?php print $data->user->uid; ?>/friends/<?php print $item->uid; ?>/ignore">Remind Me</a>
								</div>
							</div>
						<?php } ?>
					</div>
				</div>
			<?php } ?>
		<?php } ?>

		<div class="section grid">
			<?php if (sizeof($data->items->friends) > 0) { ?>
				<div class="items">
					<?php foreach ($data->items->friends as $item) { ?>
						<?php
							if ($user->uid === $data->user->uid) {
								$href = '/user/' . $data->user->uid . '/friends/' . $item->uid;
							} else {
								if ($user->uid === $item->uid) {
									$href = '/user';
								} else {
									$href = '/user/' . $user->uid . '/friends/' . $item->uid;
								}
							}

							$total_earned_flips = 0;
							$flipstuff = v2_profiles_flips_query_all($item->uid);
							foreach($flipstuff as $key=>$val) {
								if($val->progress=='100') $total_earned_flips++;
							}
						?>
						<div class="item">
							<div class="image">
								<a href="<?php print $href; ?>"><img height="126" src="<?php print $item->src; ?>" width="126" /></a>
							</div>
							<div class="name">
								<a href="<?php print $href; ?>"><?php print $item->name; ?></a>
								<span><?php print (int)$total_earned_flips; ?> Flips Earned</span>
							</div>
							<div class="actions">
								<a class="button small" href="<?php print $href; ?>">View Profile</a>
								<?php if ($user->uid === $data->user->uid) { ?>
									<a class="button small gray remove" href="/user/<?php print $data->user->uid; ?>/friends/<?php print $item->uid; ?>/remove">Unfriend</a>
								<?php } ?>
							</div>
						</div>
					<?php } ?>
				</div>
			<?php } else { ?>
				<p>There are no friends.</p>
			<?php } ?>
		</div>

	</div>

</div>

<div class="block modal" id="friends-remove" style="display:none;">
	<div class="section title">
		<h1>Are you sure you want to remove this friend?</h1>
	</div>
	<div class="section cms">
		<p>By removing this friend you will no longer have access to their profile.</p>
	</div>
	<div class="section buttons">
		<a class="button remove" href="#">Yes, Remove This Friend</a>
		<a class="button primary cancel" href="#">No, Keep This Friend</a>
	</div>
</div>
