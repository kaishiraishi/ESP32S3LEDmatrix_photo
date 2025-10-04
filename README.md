# ESP32-S3 LEDマトリックス写真表示プロジェクト

このプロジェクトは、p5.jsでWebカメラから撮影した写真を8x8のピクセルデータに変換し、ESP32-S3とNeoPixel LEDマトリックスで表示するシステムです。

## 🎯 プロジェクト概要

1. **p5.js**: Webカメラからリアルタイム映像を取得し、8x8ピクセルにモザイク化
2. **データ生成**: スペースキーを押すことで、RGB値の配列データを生成
3. **ESP32-S3**: 生成されたデータをLEDマトリックスに表示

## 📋 必要な部品

- ESP32-S3 開発ボード
- 8x8 NeoPixel LEDマトリックス（WS2812B）
- ジャンパーワイヤー
- ブレッドボード（オプション）

## 🔌 配線

| ESP32-S3 | LEDマトリックス |
|----------|----------------|
| GPIO 14  | DIN            |
| 5V       | VCC            |
| GND      | GND            |

## 📁 ファイル構成

```
ESP32S3LEDmatrix_photo/
├── ESP32S3LEDmatrix_photo.ino  # Arduino IDE用メインファイル
└── README.md                   # このファイル
```

## 🚀 使い方

### 1. p5.jsでデータ作成

以下のp5.jsコードをブラウザで実行してください：

```javascript
let video;
let mosaicSize = 8; // 8x8

function setup() {
  createCanvas(400, 400);

  let constraints = {
    video: { facingMode: "user" },
    audio: false
  };

  video = createCapture(constraints);
  video.size(mosaicSize, mosaicSize);
  video.hide();
  noStroke();
}

function draw() {
  background(0);
  video.loadPixels();

  let w = width / mosaicSize;
  let h = height / mosaicSize;

  for (let y = 0; y < mosaicSize; y++) {
    for (let x = 0; x < mosaicSize; x++) {
      let i = (y * mosaicSize + x) * 4;
      let r = video.pixels[i];
      let g = video.pixels[i + 1];
      let b = video.pixels[i + 2];
      fill(r, g, b);
      rect(x * w, y * h, w, h);
    }
  }
}

// スペースキーを押した瞬間にピクセルを二重配列で出力
function keyPressed() {
  if (key === ' ') {
    video.loadPixels();
    let data = [];

    for (let y = 0; y < mosaicSize; y++) {
      for (let x = 0; x < mosaicSize; x++) {
        let i = (y * mosaicSize + x) * 4;
        let r = video.pixels[i];
        let g = video.pixels[i + 1];
        let b = video.pixels[i + 2];
        data.push(`{${r}, ${g}, ${b}}`);
      }
    }

    // 8x8 に改行して出力
    let output = "{\n";
    for (let y = 0; y < mosaicSize; y++) {
      let row = data.slice(y * mosaicSize, (y + 1) * mosaicSize).join(", ");
      output += "  " + row + (y < mosaicSize - 1 ? ",\n" : "\n");
    }
    output += "};";

    console.log(output);
    saveCanvas("snapshot", "jpg");
  }
}
```

### 2. データの取得と設定

1. p5.jsアプリケーションを実行
2. Webカメラで撮影したい画像をフレーミング
3. **スペースキー**を押下
4. ブラウザのコンソールに出力されたRGB配列データをコピー
5. `ESP32S3LEDmatrix_photo.ino`の`imageData`配列を新しいデータで置き換え

### 3. ESP32-S3への書き込み

1. Arduino IDEで`ESP32S3LEDmatrix_photo.ino`を開く
2. 必要なライブラリをインストール：
   - Adafruit GFX Library
   - Adafruit NeoMatrix
   - Adafruit NeoPixel
3. ESP32-S3を接続してスケッチを書き込み

## ⚙️ 設定項目

### ハードウェア設定
```cpp
#define LED_PIN   14           // LEDマトリックスのデータピン
#define W 8                    // マトリックスの幅
#define H 8                    // マトリックスの高さ
#define GLOBAL_BRIGHTNESS  50  // 明るさ（0-255）
```

### マトリックス配線レイアウト
```cpp
NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
```
- 左上原点
- 行優先
- プログレッシブ（全行同じ方向）

## 🔧 カスタマイズ

### 明るさ調整
`GLOBAL_BRIGHTNESS`の値を変更して明るさを調整できます（0-255）。

### 回転調整
現在のコードは画像を反時計回りに90度回転させています。回転を変更したい場合は、setup()内の座標変換部分を修正してください。

### 解像度変更
8x8以外の解像度を使用する場合は、`W`と`H`の定数を変更し、p5.jsの`mosaicSize`も同じ値に設定してください。

## 📝 注意事項

- LEDマトリックスは多くの電流を消費するため、適切な電源供給を確保してください
- 明るさを高く設定しすぎると、ESP32-S3の電源容量を超える可能性があります
- p5.jsでWebカメラにアクセスする際は、HTTPSが必要な場合があります

## 🤝 貢献

プロジェクトの改善提案やバグ報告は、Issuesまたはプルリクエストでお願いします。

## 📄 ライセンス

このプロジェクトはMITライセンスの下で公開されています。
