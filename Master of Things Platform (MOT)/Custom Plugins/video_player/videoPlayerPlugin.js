var VideoPlayerPlugin2 = (function () {
    var myvideoPlater = function () {
        MOT_Plugin.call(this); // call plugin constructor
        this.PluginType = 'VideoPlayerPlugin2';

        this.SetParameterValue('pluginName', 'VideoPlayerPlugin2');

        this.Parameters.VideoSource = this.addPluginParameters('VideoSource', 'Input', 'Video Source', 'caption', 'set video url/source');
        this.Parameters.VideoSource.addProperty('VideoSource', 'mp4');

        this.Parameters.VideoType = this.addPluginParameters('VideoType', 'Select', ['mp4', 'youtube'], 'Video Type', 'select video type');
        this.Parameters.VideoType.addProperty('selectedValue', 'mp4');

        this.Parameters.VideoPlayerTheme = this.addPluginParameters('VideoPlayerTheme', 'Select', ['city', 'sea', 'fantasy', 'forset'], 'Video theme', 'select Video theme');
        this.Parameters.VideoPlayerTheme.addProperty('selectedValue', 'city');

        let tabsdata = {
            video1: { videoUrl: '', videoType: 'mp4', isActive: 1 },
            video2: { videoUrl: '', videoType: 'mp4', isActive: 0 },
            video3: { videoUrl: '', videoType: 'mp4', isActive: 0 },
        }
        this.Parameters.jsonArray = this.addPluginParameters('jsonArray', 'jsonArray', tabsdata, 'tabs Data', 'set your video and type');

        this.Parameters.EnablePlaylist = this.addPluginParameters('EnablePlaylist', 'True/False', 0, 'Enable Playlist', 'run playlist or single video');

        delete this.Parameters.DataSource;
        delete this.Parameters.Query;

        this.Parameters.OnStart = this.addPluginParameters('OnStart', 'event', '', 'OnStart', 'OnStart video event');
        this.Parameters.OnFinish = this.addPluginParameters('OnFinish', 'event', '', 'OnFinish', 'OnFinish video event');
    }
    extend(myvideoPlater, MOT_Plugin);
    myvideoPlater.prototype.Draw = function (WorkSapce) {
        this.PrepareWorkspace(WorkSapce)
        var date = new Date()
        var videoTageId = date.getTime();
        this.LoadAssets([], () => {
            var container = document.createElement('div')
            container.id = videoTageId

            var videoTage = document.createElement('video')
            videoTage.id = 'my-Player' + videoTageId

            var videoTheme = this.GetParameterBrName('VideoPlayerTheme').selectedValue
            var videoClassesNameTheme = `vjs-theme-${videoTheme}`
            videoTage.className = 'video-js' + videoClassesNameTheme

            container.appendChild(videoTage)
            WorkSapce.appendChild(container)

            var options = {
                controls: true,
                autoplay: true,
                preload: 'auto'
            }
            var player = videojs(videoTage.id, options)

            var videoType = this.GetParameterBrName('VideoType').selectedValue
            var videosrc = this.GetParameterValue('VideoSource')
            if (this.GetParameterValue('EnablePlaylist') == 1) {

            } else {
                player.src({
                    type: 'video/' + videoType,
                    src: videosrc
                })
            }

        });
    }
    return myvideoPlater;
});