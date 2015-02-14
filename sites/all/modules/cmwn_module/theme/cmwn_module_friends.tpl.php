<div class="friends">
<?php foreach ($friends as $friend) : ?>
  <div class="friend">
    <div>
      <a href="<?php echo url('user/'.$friend->uid); ?>">
        <?php echo $friend->getAvatar(true); ?>
        <span><?php echo $friend->name; ?></span>
      </a>
    </div>
  </div>
<?php endforeach; ?>
</div>