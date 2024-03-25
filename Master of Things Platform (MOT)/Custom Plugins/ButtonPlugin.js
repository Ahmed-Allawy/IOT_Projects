

var ButtonPlugin2 = (function () {

    var myCustomButton = function () {
        MOT_Plugin.call(this);
        this.PluginType = 'ButtonPlugin2';
        this.SetParameterValue('pluginName', 'ButtonPlugin2');

        this.Parameters.Caption = this.addPluginParameters('Caption', 'input', 'AllawyButton', 'Allawy Button', 'dec');
        this.Parameters.FontFamily = this.addPluginParameters('FontFamily', 'select', ["Arial", "Monaco", "Times New Roman"], 'dec');
        this.Parameters.FontFamily.addProperty('selectedValue', 'Monaco');
        this.Parameters.BackGroundColor = this.addPluginParameters('BackGroundColor', 'color', '', 'Back Ground Color', 'dec');
        this.Parameters.BorderRounded = this.addPluginParameters('BorderRounded', 'True/False', 0, 'Border Rounded', 'dec');
        this.Parameters.ButtonStyle = this.addPluginParameters('ButtonStyle', 'select', ["default", "primary", "success", "info", "warning", "danger"], 'Button Style', 'dec');
        this.Parameters.ButtonStyle.addProperty('selectedValue', 'default');
        this.Parameters.FontSize = this.addPluginParameters('FontSize', 'input', '15', 'font size', 'dec');
        delete this.Parameters.DataSource;
        delete this.Parameters.Query;
    }

    extend(myCustomButton, MOT_Plugin);

    myCustomButton.prototype.Draw = function (WorkSpace) {
        this.PrepareWorkspace(WorkSpace);
        var button = document.createElement("button");
        var date = new Date();
        date = date.getTime() * Math.random();
        button.id = date;

        var span = document.createElement("SPAN");

        var captionValue = this.GetParameterValue('caption');
        var caption = document.createTextNode(captionValue);

        span.style.fontFamily = this.GetParameterByName('FontFamily').selectedValue;
        span.style.fontSize = this.GetParameterValue('FontSize') + 'px';
        button.style.background = this.GetParameterValue('BackGroundColor');

        if (this.GetParameterValue('BorderRounded') == 1) {
            button.style.border = '25px';
        }

        span.appendChild(caption);
        button.appendChild(span);
        WorkSpace.appendChild(button);

        var buttonStyleValue = this.GetParameterByName('ButtonStyle').selectedValue;
        switch (buttonStyleValue) {
            case 'default':
                button.classList.add('btn-default');
                break;

            case 'primary':
                button.classList.add('btn-primary');
                break;

            case 'success':
                button.classList.add('btn-success');
                break;

            case 'info':
                button.classList.add('btn-info');
                break;

            case 'warning':
                button.classList.add('btn-warning');
                break;

            case 'danger':
                button.classList.add('btn-danger');
                break;

            default:
                break;
        }

        this.addCssClasses(button);
    }
    return myCustomButton;
}());