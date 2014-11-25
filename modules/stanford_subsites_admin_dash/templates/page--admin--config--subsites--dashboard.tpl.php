<?php
  /**
   * Dashboard Template file.
   */
?>


<?php if ($content['main_top']) : ?>
  <div class="main-top-region">
    <?php print render($content['main_top']); ?>
  </div>
<?php endif; ?>

<div class="main-content-region <?php if ($content['sidebar_second']) { print 'sidebar-second'; } ?>">
  <?php print render($content['content']); ?>
</div>

<?php if ($content['sidebar_second']) : ?>

  <div class="sidebar-second-region">
    <?php print render($content['sidebar_second']); ?>
  </div>

<?php endif; ?>
