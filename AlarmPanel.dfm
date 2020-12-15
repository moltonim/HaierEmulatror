object Form3: TForm3
  Left = 230
  Top = 125
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsDialog
  Caption = 'Alarm'
  ClientHeight = 88
  ClientWidth = 386
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 183
    Top = 72
    Width = 22
    Height = 13
    Caption = 'HEX'
  end
  object Edit1: TEdit
    Left = 5
    Top = 24
    Width = 25
    Height = 21
    TabOrder = 0
    Visible = False
  end
end
