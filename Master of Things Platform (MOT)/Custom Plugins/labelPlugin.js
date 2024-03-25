var labelPlugin2 = (function () {

    var mylabelPlugin2 = function () {
        MOT_Plugin.call(this); // call plugin constructor
        this.PluginType = 'labelPlugin2'

        this.SetParameterValue('pluginName', 'labelPlugin2');

        this.Parameters.LabelValue = this.addPluginParameters('LabelValue', 'input', 'MyLabel', 'caption', 'desc');
        this.Parameters.BorderThikness = this.addPluginParameters('BorderThikness', 'input', '5', 'Border Thikness', 'desc');

        this.Parameters.FontSize = this.addPluginParameters('FontSize', 'Select', ['6px', '8px', '10px', '12px'], 'Font Size', 'desc');
        this.Parameters.FontSize.addProperty('selectedValue', '6px');

        this.Parameters.FontFamily = this.addPluginParameters('FontFamily', 'select', ["Arial", "Monaco", "Times New Roman"], 'Font Family', 'desc');
        this.Parameters.FontFamily.addProperty('selectedValue', 'Arial');

        this.Parameters.FontStyle = this.addPluginParameters('FontStyle', 'select', ["normal", "italic"], 'Font Style', 'desc');
        this.Parameters.FontStyle.addProperty('selectedValue', 'normal');

        this.Parameters.FontWeight = this.addPluginParameters('FontWeight', 'select', ["normal", "bold"], 'Font Weight', 'desc');
        this.Parameters.FontWeight.addProperty('selectedValue', 'normal');

        this.Parameters.BorderStyle = this.addPluginParameters('BorderStyle', 'select', ["solid", "dash"], 'Border Style', 'desc');
        this.Parameters.BorderStyle.addProperty('selectedValue', 'solid');

        this.Parameters.TextRotation = this.addPluginParameters('TextRotation', 'select', ["rotate(0deg)", "rotate(90deg)", "rotate(270deg)",], 'Text Rotation', 'desc');
        this.Parameters.TextRotation.addProperty('selectedValue', "rotate(0deg)");

        this.Parameters.BorderColor = this.addPluginParameters('BorderColor', 'color', '#000000', 'Border Color', 'desc');
        this.Parameters.FontColor = this.addPluginParameters('FontColor', 'color', '#000000', 'Font Color', 'desc');

        this.Parameters.MultipleLines = this.addPluginParameters('MultipleLines', 'True/False', 0, 'Multiple Lines', 'desc');
        this.Parameters.Scroll = this.addPluginParameters('MultipleLScrollines', 'True/False', 0, 'Scroll', 'desc');

        this.Parameters.BorderRounded = this.addPluginParameters('BorderRounded', 'True/False', 0, 'Border Rounded', 'desc');
        this.Parameters.HasBroder = this.addPluginParameters('HasBroder', 'True/False', 0, 'Has Broder', 'desc');

        this.Parameters.DataSource = this.addPluginParameters('DataSource', 'sensorsList', ["no sensor", "no reading"], 'Data Source', 'desc');
    };

    extend(mylabelPlugin2, MOT_Plugin);

    mylabelPlugin2.prototype.Draw = function (WorkSpace) {

        this.PrepareWorkspace(WorkSpace);

        var spanEl = document.createElement('span');
        WorkSpace.appendChild(spanEl);

        var date = new Date();
        date = date.getDate() * Math.random();
        spanEl.id = date;

        spanEl.innerHTML = this.GetParameterValue('LabelValue');

        spanEl.style.fontSize = this.GetParameterByName('FontSize').selectedValue;
        spanEl.style.fontFamily = this.GetParameterByName('FontFamily').selectedValue;
        spanEl.style.fontStyle = this.GetParameterByName('FontStyle').selectedValue;
        spanEl.style.fontWeight = this.GetParameterByName('FontWeight').selectedValue;
        WorkSpace.style.transform = this.GetParameterByName('TextRotation').selectedValue;
        spanEl.style.float = 'left';
        spanEl.style.lineHeight = '20px';
        spanEl.style.widows = 'max-content';

        if (this.GetParameterValue('BorderRounded') == 1) {
            spanEl.style.borderRadius = '10px';
        }

        if (this.GetParameterValue('MultipleLines') == 1) {
            spanEl.style.width = this.GetParameterValue('PluginWidth') + 'px';
            spanEl.style.height = this.GetParameterValue('PluginHeight') + 'px';
            spanEl.style.wordWrap = 'break-word'
        }

        if (this.GetParameterValue('MultipleLines') == 1 && this.GetParameterValue('Scroll') == 1) {
            if (this.GetParameterValue('LabelValue').length != 0) {
                if (this.GetParameterValue('PluginWidth') / this.GetParameterValue('LabelValue').length > 7.8) {
                    spanEl.style.overflowY = '';
                } else {
                    spanEl.style.overflowY = 'scroll';
                }
            }
        }
        var dataArray = this.GetParameterValue('Query').data // like video
        // I think it should be
        // var dataArray = this.GetParameterByName('Query').data

        if (dataArray != undefined && dataArray != null) {
            spanEl.innerHTML = '';
            if (Object.keys(dataArray).length == 0) {
                spanEl.innerHTML = 'no data found';
            } else {
                var firstRecord = dataArray[0];
                for (const [key, value] of firstRecord) {
                    spanEl.innerHTML = spanEl.innerHTML + ", " + `${value}`;
                }
            }
        }
        this.addCssClasses(spanEl);
    };

    return mylabelPlugin2;
}());