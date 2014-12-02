(function($){

  // Drupal Behaviours
  // ---------------------------------------------------------------------------


  Drupal.behaviors.working_space_quick_toggle = {
    attach: function (context, settings) {
      $("#edit-subsite-workingspace").change(function(e) {
        var nid = $(this).val();
        var base = Drupal.settings.basePath;
        window.location = base + "admin/config/subsites/dashboard/toggle/" + nid;
      });
    }
  };

})(jQuery);
